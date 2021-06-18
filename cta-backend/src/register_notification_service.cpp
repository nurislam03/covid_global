#include <request/register_notification_request.h>
#include <cta_service.h>

namespace cta {

Error* RegisterNotificationRequest::GetServed(AuthService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

Error* RegisterNotificationRequest::GetServed(CTAService& cta) const {
    return cta.RegisterNotification(*this);
}

} // namespace cta