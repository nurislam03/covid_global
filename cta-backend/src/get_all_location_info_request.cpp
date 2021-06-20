#include <request/get_all_location_info_request.h>
#include <cta_service.h>

namespace cta {

GetAllLocationInfoRequest::GetAllLocationInfoRequest(int offset, int limit)
    : offset{offset}, limit{limit} {}

Error* GetAllLocationInfoRequest::GetServed(AuthService&) const {
    return new Error(Error::CODE::ERR_PASS, "");
}

Error* GetAllLocationInfoRequest::GetServed(CTAService& cta) const {
    return cta.GetAllLocationInfo(*this);
}

}
