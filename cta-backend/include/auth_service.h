/**
 * auth_service.h declars interface for authentication servic
 */

#ifndef __AUTH_SERVICE_H__
#define __AUTH_SERVICE_H__

#include <error/error.h>
#include <request/service_request.h>
#include <request/login_request.h>
#include <request/logout_request.h>
#include <service.h>

namespace cta {

class AuthService final : public Service {
    friend class LoginRequest;
    friend class LogoutRequest;

public:
    Error* Serve(const ServiceRequest& req) override;

private:
    Error* Login(const LoginRequest& loginReq);
    Error* Logout(const LogoutRequest& logoutReq);
};

}

#endif // __AUTH_SERVICE_H__