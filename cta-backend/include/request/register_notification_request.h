#ifndef __REGISTER_NOTIFICATION_REQUEST_H__
#define __REGISTER_NOTIFICATION_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct RegisterNotificationRequest final : public ServiceRequest {

    // we will be able to get user email from sessionID
    std::string sessionID;
    std::string location;

    RegisterNotificationRequest() = default; // default ctor is required by json library
    RegisterNotificationRequest(const std::string& sessionID, const std::string& location);

    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTER_NOTIFICATION_REQUEST_H__