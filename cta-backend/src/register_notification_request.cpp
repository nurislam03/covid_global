#include <request/register_notification_request.h>
#include <cta_service.h>

namespace cta {

RegisterNotificationRequest::RegisterNotificationRequest(const std::string& sessionID, const std::string& location)
    : sessionID{sessionID}, location{location} {}

Result<std::shared_ptr<ServiceResponse>> RegisterNotificationRequest::GetServed(AuthService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

Result<std::shared_ptr<ServiceResponse>> RegisterNotificationRequest::GetServed(CTAService& cta) const {
    return cta.RegisterNotification(*this);
}

} // namespace cta