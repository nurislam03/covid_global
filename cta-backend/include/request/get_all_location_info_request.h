#ifndef __GET_ALL_LOCATION_INFO_H__
#define __GET_ALL_LOCATION_INFO_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct GetAllLocationInfoRequest final : public ServiceRequest {

    int offset;
    int limit;

    GetAllLocationInfoRequest() = default;
    GetAllLocationInfoRequest(int offset, int limit);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;

};

} // namespace cta

#endif // __GET_ALL_LOCATION_INFO_H__
