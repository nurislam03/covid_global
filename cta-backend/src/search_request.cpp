#include <request/search_request.h>
#include <cta_service.h>

namespace cta {

SearchRequest::SearchRequest(const std::string& location, int offset, int limit)
    : location{location}, offset{offset}, limit{limit}
{}

Error* SearchRequest::GetServed(AuthService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

Error* SearchRequest::GetServed(CTAService& cta) const {
    return cta.Search(*this);
}

} // namespace cta