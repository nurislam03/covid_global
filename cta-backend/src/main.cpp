#include <iostream>
#include <string>
#include <list>
#include <httpserver.h>
#include <cta_service.h>
#include <auth_service.h>
#include <mongo_repository.h>

// cta-backend
// "mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority"

int main(int argc, char** argv)
{
    std::shared_ptr<cta::Repository> repo = cta::MongoRepository::Create(
        "mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority",
        "cta-backend"
    );

    std::list<std::shared_ptr<cta::Service>> services { 
        std::make_shared<cta::CTAService>(repo), std::make_shared<cta::AuthService>(repo)
    };

    cta::HTTPServer server{std::move(services)};

    std::cout << "HTTP server listening on http://localhost:4000" << std::endl;

    auto err = server.Listen("localhost", 4000);
    if(err) {
        // TODO: add logger
        std::cout << err->getMessage() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
