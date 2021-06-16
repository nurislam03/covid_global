#ifndef __LOGOUT_REQUEST_H__
#define __LOGOUT_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct LogoutRequest final : public ServiceRequest {

public:
    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __LOGOUT_REQUEST_H__