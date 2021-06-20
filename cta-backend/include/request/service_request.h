#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <error/error.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

class AuthService;
class CTAService;

struct ServiceRequest {
    virtual Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const = 0;
    virtual Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const = 0;
};
 
}
#endif // __REQUEST_H__