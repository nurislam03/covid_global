#include <response/get_all_location_info_response.h>

namespace cta {

GetAllLocationInfoResponse::GetAllLocationInfoResponse(std::list<std::shared_ptr<LocationInfo>>& info)
    : info{info} {}

std::string GetAllLocationInfoResponse::Serialize(Serializer& serializer) const {
    return serializer.Serialize(*this);
}

}