#ifndef __LOGIN_RESPONSE_H__
#define __LOGIN_RESPONSE_H__

#include <string>
#include <list>
#include <response/service_response.h>
#include <serializable.h>

namespace cta {

struct  LoginResponse final : public ServiceResponse {
    std::string sessionID;
    std::string name;
    std::string email;
    std::list<std::string> subscriptions;

    LoginResponse(const std::string& name, const std::string& email
        , const std::string& sessionID, std::list<std::string>&& subscriptions);

    std::string Serialize(const Serializer&) const override;
};

}

#endif // __LOGIN_RESPONSE_H__
