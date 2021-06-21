#include <iostream>
#include <string>
#include <list>
#include <httpserver.h>
#include <cta_service.h>
#include <auth_service.h>
#include <mongo_repository.h>


int main(int argc, char** argv)
{
    std::shared_ptr<cta::Repository> repo = std::make_shared<cta::MongoRepository>();

    std::list<std::shared_ptr<cta::Service>> services { 
        std::make_shared<cta::CTAService>(repo), std::make_shared<cta::AuthService>(repo)
    };

    cta::HTTPServer server{std::move(services)};

    auto err = server.Listen("localhost", 4000);
    if(err) {
        // TODO: add logger
        std::cout << err->getMessage() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}