#ifndef __UNREGISTER_NOTIFICATION_REQUEST_H__
#define __UNREGISTER_NOTIFICATION_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct UnRegisterNotificationRequest final : public ServiceRequest {

    std::string sessionID;
    std::string location;

    UnRegisterNotificationRequest() = default; // default ctor is required by json library
    UnRegisterNotificationRequest(const std::string& sessionID, const std::string& location);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __UNREGISTER_NOTIFICATION_REQUEST_H__
