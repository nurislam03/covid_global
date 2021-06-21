#ifndef __SEARCH_RESPONSE_H__
#define __SEARCH_RESPONSE_H__

#include <memory>
#include <response/service_response.h>
#include <model/location_info.h>
#include <serializable.h>

namespace cta {

struct SearchResponse final : public ServiceResponse, public Serializable {
    std::shared_ptr<LocationInfo> info;

    SearchResponse() = default;
    SearchResponse(std::shared_ptr<LocationInfo> info);

    std::string Serialize(Serializer&) const override;
};


}

#endif // __SEARCH_RESPONSE_H__