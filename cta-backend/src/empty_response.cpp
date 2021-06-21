#include <response/empty_response.h>

namespace cta {

std::string EmptyResponse::Serialize(Serializer& serializer) const {
    return serializer.Serialize(*this);
}
}