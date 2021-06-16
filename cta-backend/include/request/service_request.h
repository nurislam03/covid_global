#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <error/error.h>

namespace cta {

class AuthService;
class CTAService;

class ServiceRequest {
public:
    virtual Error* GetServed(AuthService& auth) const = 0;
    virtual Error* GetServed(CTAService& cta) const = 0;
};
 
}
#endif // __REQUEST_H__