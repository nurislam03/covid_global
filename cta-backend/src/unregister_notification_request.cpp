#include <request/unregister_notification_request.h>
#include <cta_service.h>

namespace cta {

UnRegisterNotificationRequest::UnRegisterNotificationRequest(const std::string& sessionID, const std::string& location)
    : sessionID{sessionID}, location{location} {}

Result<std::shared_ptr<ServiceResponse>> UnRegisterNotificationRequest::GetServed(AuthService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

Result<std::shared_ptr<ServiceResponse>> UnRegisterNotificationRequest::GetServed(CTAService& cta) const {
    return cta.UnRegisterNotification(*this);
}

} // namespace cta