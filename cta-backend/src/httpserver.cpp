#include <httpserver.h>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>
#include <json_serializer.h>
#include <cassert>

namespace cta {

int errorToHTTPStatusCode(std::shared_ptr<Error> err) {
    static const std::unordered_map<Error::CODE, int> err2status {
        {Error::CODE::ERR_NOTFOUND, 404},
        {Error::CODE::ERR_REPO, 500},
        {Error::CODE::ERR_UNAUTHORIZED, 401},
        {Error::CODE::ERR_DUPLICATE_USER, 409},
        {Error::CODE::ERR_VALIDATION, 400},
        {Error::CODE::ERR_WRONG_PASSWORD, 403},
        {Error::CODE::ERR_BLOCKED, 403},
        {Error::CODE::ERR_UNKNOWN, 500}
    };

    try {
        return err2status.at(err->getCode());
    }
    catch(const std::out_of_range& ) {
        // TODO: log exception
        return 500;
    }
    
    assert(false); // should never reach this statement
    return 500;
}


HTTPServer::HTTPServer(std::list<std::shared_ptr<Service>>&& services)
    : services{services} {}


std::shared_ptr<Error> HTTPServer::Listen(const std::string& addr, int port) {

    using json = nlohmann::json;

    httplib::Server svr;

    svr.Options(R"(/.*)", [&](const auto& req, auto& res) {
        res.status = 200;
    });

    svr.Post("/", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::GetAllLocationInfo, req);
    });

    svr.Post("/search", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::Search, req);
    });

    svr.Post("/registernotification", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::RegisterNotification, req);
    });

    svr.Post("/unregisternotification", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::UnRegisterNotification, req);
    });

    svr.Post("/login", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::Login, req);
    });

    svr.Post("/logout", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::Logout, req);
    });

    svr.Post("/register", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::Registration, req);
    });

    svr.set_post_routing_handler([](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Methods", " POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Connection", "close");
    });


    svr.set_exception_handler([](const auto& req, auto& res, std::exception &e) {
        std::cout << "exception at request handler: " << e.what() << std::endl;

        res.status = 500;
        res.set_content("Internal server error", "text/plain");
    });

    svr.listen(addr.c_str(), port);

    return nullptr;
}

HTTPResponse HTTPServer::HandleRequest(RequestValidator::TYPE type, const HTTPRequest& req) {
    
    std::cout << "request received of type: " << static_cast<int>(type) << std::endl;
    
    auto [serviceReq, err] = requestValidator->ValidateRequest(type, req);

    HTTPResponse res;

    if (err && err->getCode() == Error::CODE::ERR_VALIDATION) {
        
        res.status = 400;
        res.set_content(err->getMessage(), "text/plain");

        std::cout << "Handle Request error: " << static_cast<int> (err->getCode()) << " message: " << err->getMessage() << std::endl;
        return res;
    }

    // TODO: Need to check auth for some request

    for(auto service: services) {

        auto [result, err] = service->Serve(*serviceReq);
        if (err != nullptr) {
            if(err->getCode() == Error::CODE::ERR_PASS) continue;

            res.status = errorToHTTPStatusCode(err);
            res.set_content(err->getMessage(), "text/plain"); 
            // todo: remove
            std::cout << "Handle Request error: " << static_cast<int> (err->getCode()) << " message: " << err->getMessage() << std::endl;
            return res;
        }

        assert(result != nullptr);
        res.set_content(result->Serialize(JsonSerializer{}), "application/json");
        res.status = 200;
        return res;
    }

    return res;
}

}
