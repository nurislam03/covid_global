#ifndef __LOGIN_REQUEST_H__
#define __LOGIN_REQUEST_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct LoginRequest final : public ServiceRequest {
    
    std::string email;
    std::string password;

    LoginRequest() = default; // default ctor is required by json library
    LoginRequest(const std::string& email, const std::string& password);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __LOGIN_REQUEST_H__