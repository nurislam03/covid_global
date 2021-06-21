#ifndef __LOGIN_RESPONSE_H__
#define __LOGIN_RESPONSE_H__

#include <string>
#include <response/service_response.h>
#include <serializable.h>

namespace cta {

struct  LoginResponse final : public ServiceResponse {
    std::string sessionID;

    // TODO: add name
    // TODO: add emmail
    // TODO: add list of subscription

    LoginResponse() = default;
    LoginResponse(const std::string& sessionID);

    std::string Serialize(const Serializer&) const override;
};

}

#endif // __LOGIN_RESPONSE_H__