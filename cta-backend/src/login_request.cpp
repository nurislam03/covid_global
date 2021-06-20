#include <request/login_request.h>
#include <auth_service.h>

namespace cta {

LoginRequest::LoginRequest(const std::string& email, const std::string& password)
    : email{email}, password{password}
{}

Result<std::shared_ptr<ServiceResponse>> LoginRequest::GetServed(AuthService& auth) const {
    return auth.Login(*this);
}

Result<std::shared_ptr<ServiceResponse>> LoginRequest::GetServed(CTAService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

} // namespace cta