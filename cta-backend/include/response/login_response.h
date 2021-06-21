#ifndef __LOGIN_RESPONSE_H__
#define __LOGIN_RESPONSE_H__

#include <string>
#include <response/service_response.h>
#include <serializable.h>

namespace cta {

struct  LoginResponse final : public ServiceResponse, public Serializable {
    std::string sessionID;

    LoginResponse() = default;
    LoginResponse(const std::string& sessionID);

    std::string Serialize(Serializer&) const override;
};

}


#endif // __LOGIN_RESPONSE_H__