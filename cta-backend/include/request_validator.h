#ifndef __REQUEST_VALIDATOR_H__
#define __REQUEST_VALIDATOR_H__

#include <memory>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>
#include <error/error.h>
#include <request/service_request.h>

namespace cta {

using json = nlohmann::json;
using HTTPRequest = httplib::Request;

class RequestValidator {

public:

    enum class TYPE{
        Registration,
        Login,
        Logout,
        Search,
        RegisterNotification
    };

    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateRequest(TYPE type, const HTTPRequest& req);

private:
    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateRegistrationReuest(const HTTPRequest& req);
    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateLoginReuest(const HTTPRequest& req);
    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateLogoutReuest(const HTTPRequest& req);

    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateSearchReuest(const HTTPRequest& req);
    std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>> ValidateRegisterNotificationReuest(const HTTPRequest& req);
};

}

#endif // __REQUEST_VALIDATOR_H__