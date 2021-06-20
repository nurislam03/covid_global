#ifndef __GET_ALL_LOCATION_INFO_RESPONSE_H__
#define __GET_ALL_LOCATION_INFO_RESPONSE_H__

#include <list>
#include <memory>
#include <response/service_response.h>
#include <model/location_info.h>


namespace cta {

struct GetAllLocationInfoResponse final : public ServiceResponse {
    std::list<std::shared_ptr<LocationInfo>> info;

    GetAllLocationInfoResponse() = default;
    GetAllLocationInfoResponse(std::list<std::shared_ptr<LocationInfo>>& info);
};

}

#endif // __GET_ALL_LOCATION_INFO_RESPONSE_H__
