#ifndef __LOGIN_REQUEST_H__
#define __LOGIN_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct LoginRequest final : public ServiceRequest {

public:
    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __LOGIN_REQUEST_H__