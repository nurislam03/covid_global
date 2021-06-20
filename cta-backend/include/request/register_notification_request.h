#ifndef __REGISTER_NOTIFICATION_REQUEST_H__
#define __REGISTER_NOTIFICATION_REQUEST_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct RegisterNotificationRequest final : public ServiceRequest {

    // we will be able to get user email from sessionID
    std::string sessionID;
    std::string location;

    RegisterNotificationRequest() = default; // default ctor is required by json library
    RegisterNotificationRequest(const std::string& sessionID, const std::string& location);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTER_NOTIFICATION_REQUEST_H__