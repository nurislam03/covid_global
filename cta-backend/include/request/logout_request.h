#ifndef __LOGOUT_REQUEST_H__
#define __LOGOUT_REQUEST_H__

#include <request/service_request.h>
#include <result.h>
#include <response/service_response.h>

namespace cta {

struct LogoutRequest final : public ServiceRequest {

    std::string sessionID;

    LogoutRequest() = default; // default ctor is required by json library
    LogoutRequest(const std::string& sessionID);

    Result<std::shared_ptr<ServiceResponse>> GetServed(AuthService& auth) const override;
    Result<std::shared_ptr<ServiceResponse>> GetServed(CTAService& cta) const override;
};

}

#endif // __LOGOUT_REQUEST_H__