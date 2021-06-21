#include <response/search_response.h>

namespace cta {

SearchResponse::SearchResponse(std::shared_ptr<LocationInfo> info)
    : info{info} {}

std::string SearchResponse::Serialize(Serializer& serializer) const {
    return serializer.Serialize(*this);
}

}