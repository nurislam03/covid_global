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

// cta-backend
// "mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority"

int main(int argc, char** argv)
{
    std::shared_ptr<cta::MongoRepository> repo = cta::MongoRepository::Create(
        "mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority",
        "cta-backend"
    );

    if(!repo->Ping()) {
        std::cout << "DB ping error\n";
        exit(EXIT_FAILURE);
    }
    
    auto notifier = std::make_shared<cta::HTTPNotifier>("https://ctaemailserver.herokuapp.com");

    auto ctaService = std::make_shared<cta::CTAService>(repo, notifier, "http://example.com");
    auto authService = std::make_shared<cta::AuthService>(repo);

    std::list<std::shared_ptr<cta::Service>> services {ctaService, authService};

    cta::Crontab crontab("0 */1 * * * ?", ctaService);

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
