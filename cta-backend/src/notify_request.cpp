#include <request/notify_request.h>
#include <cta_service.h>

namespace cta {

Result<std::shared_ptr<ServiceResponse>> NotifyRequest::GetServed(AuthService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

Result<std::shared_ptr<ServiceResponse>> NotifyRequest::GetServed(CTAService& cta) const {
    return cta.NotifySubscriber(*this);
}

}