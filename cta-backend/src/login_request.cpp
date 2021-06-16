#include <request/login_request.h>
#include <auth_service.h>

namespace cta {

Error* LoginRequest::GetServed(AuthService& auth) const {
    return auth.Login(*this);
}

Error* LoginRequest::GetServed(CTAService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

} // namespace cta