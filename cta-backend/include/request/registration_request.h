#ifndef __REGISTRATION_REQUEST_H__
#define __REGISTRATION_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct RegistrationRequest final : public ServiceRequest {

    std::string email;
    std::string password;
    std::string name;

    RegistrationRequest() = default; // default ctor is required by json library
    RegistrationRequest(const std::string& email, const std::string& password, const std::string name);

    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTRATION_REQUEST_H__