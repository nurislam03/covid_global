#ifndef __REQUEST_VALIDATOR_H__
#define __REQUEST_VALIDATOR_H__

#include <memory>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>
#include <error/error.h>
#include <request/service_request.h>
#include <result.h>

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

    Result<std::shared_ptr<ServiceRequest>> ValidateRequest(TYPE type, const HTTPRequest& req);

private:
    Result<std::shared_ptr<ServiceRequest>> ValidateRegistrationReuest(const HTTPRequest& req);
    Result<std::shared_ptr<ServiceRequest>> ValidateLoginReuest(const HTTPRequest& req);
    Result<std::shared_ptr<ServiceRequest>> ValidateLogoutReuest(const HTTPRequest& req);
    
    Result<std::shared_ptr<ServiceRequest>> ValidateSearchReuest(const HTTPRequest& req);
    Result<std::shared_ptr<ServiceRequest>> ValidateRegisterNotificationReuest(const HTTPRequest& req);
};

}

#endif // __REQUEST_VALIDATOR_H__