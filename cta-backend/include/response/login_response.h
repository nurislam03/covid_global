#ifndef __LOGIN_RESPONSE_H__
#define __LOGIN_RESPONSE_H__

#include <string>
#include <response/service_response.h>

namespace cta {

struct  LoginResponse final : public ServiceResponse {
    std::string sessionID;

    LoginResponse() = default;
    LoginResponse(const std::string& sessionID);
};

}


#endif // __LOGIN_RESPONSE_H__