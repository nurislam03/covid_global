#ifndef __REGISTRATION_REQUEST_H__
#define __REGISTRATION_REQUEST_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct RegistrationRequest final : public ServiceRequest {

    std::string email;
    std::string password;
    std::string name;

    RegistrationRequest() = default; // default ctor is required by json library
    RegistrationRequest(const std::string& email, const std::string& password, const std::string name);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTRATION_REQUEST_H__