#include <request/logout_request.h>
#include <auth_service.h>

namespace cta {

LogoutRequest::LogoutRequest(const std::string& sessionID)
    : sessionID{sessionID} {}

Result<std::shared_ptr<ServiceResponse>> LogoutRequest::GetServed(AuthService& auth) const {
    return auth.Logout(*this);
}

Result<std::shared_ptr<ServiceResponse>> LogoutRequest::GetServed(CTAService& cta) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

} // namespace cta