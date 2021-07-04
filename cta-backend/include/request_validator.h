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
        RegisterNotification,
        UnRegisterNotification,
        GetAllLocationInfo
    };

    Result<std::shared_ptr<ServiceRequest>> ValidateRequest(TYPE type, const HTTPRequest& req);

private:
    template <typename T>
    Result<std::shared_ptr<ServiceRequest>> Validate(const HTTPRequest& req) {
        try{
            return make_result(
                std::make_shared<T>(
                    json::parse(req.body).get<T>()
                )
            );
        } catch (std::exception&) {
            return make_result(
                nullptr,
                std::make_shared<Error>(
                    Error::CODE::ERR_VALIDATION,
                    R"(parsing error, request body must be json)"
                )
            ); 
        }
    }
};

}

#endif // __REQUEST_VALIDATOR_H__