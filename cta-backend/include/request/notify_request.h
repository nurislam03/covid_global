#ifndef __NOTIFY_REQUEST_H__
#define __NOTIFY_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct NotifyRequest final : public ServiceRequest {
    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}
#endif // __NOTIFY_REQUEST_H__