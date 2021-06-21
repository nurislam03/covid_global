#include <httpserver.h>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>

namespace cta {

// TODO: refactor this method

std::shared_ptr<Error> HTTPServer::Listen(const std::string& addr, int port) {

    using json = nlohmann::json;

    httplib::Server svr;

    svr.Post("/", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::GetAllLocationInfo, req);
    });

    svr.Post("/search", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::Search, req);
    });

    svr.Post("/registernotification", [this](const httplib::Request& req, httplib::Response& res) {
        res = HandleRequest(RequestValidator::TYPE::RegisterNotification, req);
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

    svr.listen(addr.c_str(), port);

    return nullptr;
}

HTTPResponse HTTPServer::HandleRequest(RequestValidator::TYPE type, const HTTPRequest& req) {
    auto [serviceReq, err] = requestValidator->ValidateRequest(type, req);
    
    HTTPResponse res;

    if (err->getCode() == Error::CODE::ERR_VALIDATION) {
        
        res.status = 400;
        return res;
    }

    // TODO: Need to check auth for some request

    for(auto service: services) {

        auto [result, err] = service->Serve(*serviceReq);
        if (err == nullptr) {
            // TODO: set http response content
            res.status = 200;
            return res;
        }

        // TODO: handle error case
    }

    return res;
}

}