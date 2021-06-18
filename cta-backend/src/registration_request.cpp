#include <request/registration_request.h>
#include <auth_service.h>

namespace cta {

Error* RegistrationRequest::GetServed(AuthService& auth) const {
    return auth.Register(*this);
}

Error* RegistrationRequest::GetServed(CTAService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

} // namespace cta