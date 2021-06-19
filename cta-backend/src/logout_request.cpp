#include <request/logout_request.h>
#include <auth_service.h>

namespace cta {

LogoutRequest::LogoutRequest(const std::string& sessionID)
    : sessionID{sessionID} {}

Error* LogoutRequest::GetServed(AuthService& auth) const {
    return auth.Logout(*this);
}

Error* LogoutRequest::GetServed(CTAService& cta) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

} // namespace cta