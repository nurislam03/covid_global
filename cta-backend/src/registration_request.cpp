#include <request/registration_request.h>
#include <auth_service.h>

namespace cta {

RegistrationRequest::RegistrationRequest(const std::string& email, const std::string& password, const std::string name)
    : email{email}, password{password}, name{name} 
{}

Result<std::shared_ptr<ServiceResponse>> RegistrationRequest::GetServed(AuthService& auth) const {
    return auth.Register(*this);
}

Result<std::shared_ptr<ServiceResponse>> RegistrationRequest::GetServed(CTAService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

} // namespace cta