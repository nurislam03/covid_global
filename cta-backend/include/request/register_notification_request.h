#ifndef __REGISTER_NOTIFICATION_REQUEST_H__
#define __REGISTER_NOTIFICATION_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct RegisterNotificationRequest final : public ServiceRequest {

public:
    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTER_NOTIFICATION_REQUEST_H__