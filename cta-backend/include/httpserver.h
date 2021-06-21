#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include <string>
#include <error/error.h>
#include <request_validator.h>
#include <service.h>
#include <list>
#include <request_validator.h>
#include <cpp-httplib/httplib.h>

namespace cta {

using HTTPRequest = httplib::Request;
using HTTPResponse = httplib::Response;

class HTTPServer final {

    std::shared_ptr<RequestValidator> requestValidator;
    std::list<std::shared_ptr<Service>> services;

    HTTPResponse HandleRequest(RequestValidator::TYPE type, const HTTPRequest& req);

public:
    // ctor
    HTTPServer(std::list<std::shared_ptr<Service>>&& services);

    std::shared_ptr<Error> Listen(const std::string& addr, int port);
};

}
#endif // __HTTP_SERVER_H__
