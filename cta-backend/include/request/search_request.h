#ifndef __SEARCH_REQUEST_H__
#define __SEARCH_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct SearchRequest final : public ServiceRequest {

public:
    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __SEARCH_REQUEST_H__