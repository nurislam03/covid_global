#include <response/login_response.h>

namespace cta {

LoginResponse::LoginResponse(const std::string& sessionID)
    : sessionID{sessionID} {}

std::string LoginResponse::Serialize(const Serializer& serializer) const {
    return serializer.Serialize(*this);
}

}