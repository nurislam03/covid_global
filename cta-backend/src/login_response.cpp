#include <response/login_response.h>

namespace cta {

LoginResponse::    LoginResponse(const std::string& name, const std::string& email
    , const std::string& sessionID, std::list<std::string>&& subscriptions)
    : name{name}, email{email}, sessionID{sessionID}, subscriptions{subscriptions} {}

std::string LoginResponse::Serialize(const Serializer& serializer) const {
    return serializer.Serialize(*this);
}

}