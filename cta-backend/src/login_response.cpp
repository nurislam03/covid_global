#include <response/login_response.h>

namespace cta {

LoginResponse::LoginResponse(const std::string& sessionID)
    : sessionID{sessionID} {}

}