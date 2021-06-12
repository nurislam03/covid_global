/**
 * auth_service.h declars interface for authentication servic
 */

#include <error/error.h>
#include <request.h>

namespace cta {

class IAuthService {
    virtual Error Login(const LoginRequest& loginReq) = 0;
    virtual Error Logout(const LogoutRequest& logoutReq) = 0;
};

}