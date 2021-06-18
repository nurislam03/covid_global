#include <auth_service.h>

namespace cta {

Error* AuthService::Serve(const ServiceRequest& req) {
    return req.GetServed(*this);
}

Error* AuthService::Register(const RegistrationRequest& regReq){
    return nullptr;
}

Error* AuthService::Login(const LoginRequest& req) {
    return nullptr;
}

Error* AuthService::Logout(const LogoutRequest& req) {
    return nullptr;
}

}