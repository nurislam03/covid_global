#include <iostream>
#include <string>
#include <list>
#include <httpserver.h>
#include <cta_service.h>
#include <auth_service.h>
#include <mongo_repository.h>
// #include <email_notifier.h>
#include <httpnotifier.h>
#include <crontab.h>
#include <cstdlib>

const std::string ENV_DB_CONNECTION_URL = "DB_CONNECTION_URL";
const std::string ENV_DB_NAME = "DB_NAME";
const std::string ENV_NOTIFICATION_SERVER_URL = "NOTIFICATION_SERVER_URL";
const std::string ENV_FRONTEND_DETAILS_PAGE_URL = "FRONTEND_DETAILS_PAGE_URL";
const std::string ENV_NOTIFICATION_CRONTAB = "NOTIFICATION_CRONTAB";
const std::string ENV_SERVER_PORT = "SERVER_PORT";

// cta-backend
// "mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority"

// Notification server
// "https://ctaemailserver.herokuapp.com"

// crontab
// "0 */1 * * * ?"

template <typename T>
T getEnv(const std::string& var) {
    auto val = std::getenv(var.c_str());
    if (!val) {
        std::cout << "Env var '" << var << "' not found" << std::endl;
        return "";
    }

    return val;
}

template <>
int getEnv<int>(const std::string& var) {
    auto val = std::getenv(var.c_str());
    if (!val) {
        std::cout << "Env var '" << var << "' not found" << std::endl;
        return 0;
    }

    return std::atoi(val);
}

int main(int argc, char** argv)
{

    const std::string dburl = getEnv<std::string>(ENV_DB_CONNECTION_URL);
    const std::string dbname = getEnv<std::string>(ENV_DB_NAME);
    const std::string notification_server_url = getEnv<std::string>(ENV_NOTIFICATION_SERVER_URL);
    const std::string frontend_details_page_url = getEnv<std::string>(ENV_FRONTEND_DETAILS_PAGE_URL);
    const std::string notification_crontab = getEnv<std::string>(ENV_NOTIFICATION_CRONTAB);
    const int port = getEnv<int>(ENV_SERVER_PORT);

    std::shared_ptr<cta::MongoRepository> repo = cta::MongoRepository::Create(dburl, dbname);

    if(!repo->Ping()) {
        std::cout << "DB ping error\n";
        exit(EXIT_FAILURE);
    }
    
    auto notifier = std::make_shared<cta::HTTPNotifier>(notification_server_url);

    auto ctaService = std::make_shared<cta::CTAService>(repo, notifier, frontend_details_page_url);
    auto authService = std::make_shared<cta::AuthService>(repo);

    std::list<std::shared_ptr<cta::Service>> services {ctaService, authService};

    cta::Crontab crontab(notification_crontab, ctaService);

    auto err = crontab.Start();
    if (err) {
        std::cout << err->getMessage() << std::endl;
        exit(EXIT_FAILURE);
    }

    cta::HTTPServer server{std::move(services)};

    std::cout << "HTTP server listening on http://localhost:4000" << std::endl;

    err = server.Listen("localhost", 4000);
    if(err) {
        // TODO: add logger
        std::cout << err->getMessage() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
