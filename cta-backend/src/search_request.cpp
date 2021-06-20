#include <request/search_request.h>
#include <cta_service.h>

namespace cta {

SearchRequest::SearchRequest(const std::string& location)
    : location{location}
{}

Result<std::shared_ptr<ServiceResponse>> SearchRequest::GetServed(AuthService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

Result<std::shared_ptr<ServiceResponse>> SearchRequest::GetServed(CTAService& cta) const {
    return cta.Search(*this);
}

} // namespace cta