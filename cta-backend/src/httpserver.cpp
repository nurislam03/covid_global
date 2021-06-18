#include <httpserver.h>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>

namespace cta {

// TODO: refactor this method

std::shared_ptr<Error> HTTPServer::Listen(const std::string& addr, int port) {

    using json = nlohmann::json;

    httplib::Server svr;

    svr.set_logger([](const auto& req, const auto& res) {
        //std::cout << req << " " << res << std::endl;
    });

    svr.Post("/search", [](const httplib::Request& req, httplib::Response& res) {

        // TODO: remove these and implement the actual method

        // if (req.has_param("key")) {
        // auto val = req.get_param_value("key");
        // std::cout << "param, key: " << val << std::endl;
        // }

        // std::cout << "body: " << req.body << std::endl;
        // auto jsn = json::parse(req.body);
        // std::cout << "json body: " << jsn.dump(2) << std::endl;
        // res.set_content(jsn.dump(2), "application/json");
    });

    svr.listen(addr.c_str(), port);
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

        // TODO: make Serve method take std::shared_ptr
        if (service->Serve(*serviceReq) == nullptr) {
            // TODO: set http response content
            res.status = 200;
            return res;
        }
    }
}

}