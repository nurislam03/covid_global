#include <request/register_notification_request.h>
#include <cta_service.h>

namespace cta {

RegisterNotificationRequest::RegisterNotificationRequest(const std::string& sessionID, const std::string& location)
    : sessionID{sessionID}, location{location} {}

Error* RegisterNotificationRequest::GetServed(AuthService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

Error* RegisterNotificationRequest::GetServed(CTAService& cta) const {
    return cta.RegisterNotification(*this);
}

} // namespace cta