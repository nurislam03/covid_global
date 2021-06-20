#ifndef __SEARCH_REQUEST_H__
#define __SEARCH_REQUEST_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct SearchRequest final : public ServiceRequest {

    std::string location;

    SearchRequest() = default; // default ctor is required by json library
    SearchRequest(const std::string& location);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __SEARCH_REQUEST_H__