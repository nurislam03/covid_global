/**
 * auth_service.h declars interface for authentication servic
 */

#ifndef __AUTH_SERVICE_H__
#define __AUTH_SERVICE_H__

#include <error/error.h>
#include <request/service_request.h>
#include <request/login_request.h>
#include <request/logout_request.h>
#include <request/registration_request.h>
#include <service.h>
#include <repository.h>
#include <response/login_response.h>
#include <response/empty_response.h>

namespace cta {

class AuthService final : public Service {
    friend class LoginRequest;
    friend class LogoutRequest;
    friend class RegistrationRequest;

    std::shared_ptr<Repository> repo;

public:
    AuthService(std::shared_ptr<Repository> repo);

    // TODO: check if this method can be moved to base class
    Result<std::shared_ptr<ServiceResponse>> Serve(const ServiceRequest& req) override;

private:
    Result<std::shared_ptr<EmptyResponse>> Register(const RegistrationRequest& regReq);
    Result<std::shared_ptr<LoginResponse>> Login(const LoginRequest& loginReq);
    Result<std::shared_ptr<EmptyResponse>> Logout(const LogoutRequest& logoutReq);
};

}

#endif // __AUTH_SERVICE_H__