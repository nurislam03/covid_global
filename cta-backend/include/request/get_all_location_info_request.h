#ifndef __GET_ALL_LOCATION_INFO_H__
#define __GET_ALL_LOCATION_INFO_H__

#include <request/service_request.h>

namespace cta {

struct GetAllLocationInfoRequest final : public ServiceRequest {

    int offset;
    int limit;

    GetAllLocationInfoRequest() = default;
    GetAllLocationInfoRequest(int offset, int limit);

    Error* GetServed(AuthService& auth) const override;
    Error* GetServed(CTAService& cta) const override;

};

} // namespace cta

#endif // __GET_ALL_LOCATION_INFO_H__
