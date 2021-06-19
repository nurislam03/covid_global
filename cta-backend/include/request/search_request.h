#ifndef __SEARCH_REQUEST_H__
#define __SEARCH_REQUEST_H__

#include <request/service_request.h>

namespace cta {

struct SearchRequest final : public ServiceRequest {

    std::string location;
    int offset;
    int limit;

    SearchRequest() = default; // default ctor is required by json library
    SearchRequest(const std::string& location, int offset, int limit);

    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;
};

}

#endif // __SEARCH_REQUEST_H__