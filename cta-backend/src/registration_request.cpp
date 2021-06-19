#include <request/registration_request.h>
#include <auth_service.h>

namespace cta {

RegistrationRequest::RegistrationRequest(const std::string& email, const std::string& password, const std::string name)
    : email{email}, password{password}, name{name} 
{}

Error* RegistrationRequest::GetServed(AuthService& auth) const {
    return auth.Register(*this);
}

Error* RegistrationRequest::GetServed(CTAService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

} // namespace cta