#include <request/get_all_location_info_request.h>
#include <cta_service.h>

namespace cta {

GetAllLocationInfoRequest::GetAllLocationInfoRequest(int offset, int limit)
    : offset{offset}, limit{limit} {}

Result<std::shared_ptr<ServiceResponse>> GetAllLocationInfoRequest::GetServed(AuthService&) const {
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_PASS, ""));
}

Result<std::shared_ptr<ServiceResponse>> GetAllLocationInfoRequest::GetServed(CTAService& cta) const {
    return cta.GetAllLocationInfo(*this);
}

}
