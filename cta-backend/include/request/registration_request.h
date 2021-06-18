#ifndef __REGISTRATION_REQUEST_H__
#define __REGISTRATION_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct RegistrationRequest final : public ServiceRequest {

public:
    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __REGISTRATION_REQUEST_H__