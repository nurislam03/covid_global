#include <request_validator.h>
#include <request/registration_request.h>
#include <request/login_request.h>
#include <request/logout_request.h>
#include <request/search_request.h>
#include <request/register_notification_request.h>


namespace cta {

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateRequest(TYPE type, const HTTPRequest& req) {
    switch (type)
    {
    case TYPE::Registration:
        return ValidateRegistrationReuest(req);
    case TYPE::Login:
        return ValidateLoginReuest(req);
    case TYPE::Logout:
        return ValidateLogoutReuest(req);
    case TYPE::Search:
        return ValidateSearchReuest(req);
    case TYPE::RegisterNotification:
        return ValidateRegisterNotificationReuest(req);
    }
}

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateRegistrationReuest(const HTTPRequest& req) {
    return std::make_pair(std::make_shared<RegistrationRequest>(), nullptr);
}

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateLoginReuest(const HTTPRequest& req) {
    return std::make_pair(std::make_shared<LoginRequest>(), nullptr);
}

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateLogoutReuest(const HTTPRequest& req){
    return std::make_pair(std::make_shared<LogoutRequest>(), nullptr);
}

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateSearchReuest(const HTTPRequest& req) {
    return std::make_pair(std::make_shared<SearchRequest>(), nullptr);
}

std::pair<std::shared_ptr<ServiceRequest>, std::shared_ptr<Error>>
RequestValidator::ValidateRegisterNotificationReuest(const HTTPRequest& req) {
    return std::make_pair(std::make_shared<RegisterNotificationRequest>(), nullptr);
}

}