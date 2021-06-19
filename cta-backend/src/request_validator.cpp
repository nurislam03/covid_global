#include <request_validator.h>
#include <request/registration_request.h>
#include <request/login_request.h>
#include <request/logout_request.h>
#include <request/search_request.h>
#include <request/register_notification_request.h>
#include <json/json.hpp>


namespace cta {

// TODO: [improvement] try using json validator library (https://github.com/pboettch/json-schema-validator) for validation

const int DEFAULT_SEARCH_OFFSET = 0;
const int DEFAULT_SEARCH_LIMIT = 20;

using json = nlohmann::json;

// deserialization helper functions

void from_json(const json& j, LogoutRequest& lr) {
    j.at("sessionID").get_to(lr.sessionID);
}

void from_json(const json& j, LoginRequest& lr) {
    j.at("email").get_to(lr.email);
    j.at("password").get_to(lr.password);
}

void from_json(const json& j, RegisterNotificationRequest& rnr) {
    j.at("sessionID").get_to(rnr.sessionID);
    j.at("location").get_to(rnr.location);
}

void from_json(const json& j, RegistrationRequest& rr) {
    j.at("email").get_to(rr.email);
    j.at("password").get_to(rr.password);
    j.at("name").get_to(rr.name);
}

// -----------------------------

Result<std::shared_ptr<ServiceRequest>>
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

    // it is unlikely to reach here, but keeping it to make the compiler shut up about the retrun statement
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_UNKNOWN, "Unknown request"));
}

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateRegistrationReuest(const HTTPRequest& req) {
    try{
        return make_result(
            std::make_shared<RegistrationRequest>(
                json::parse(req.body).get<RegistrationRequest>()
            )
        );
    } catch (std::exception&) {
        return make_result(
            nullptr,
            std::make_shared<Error>(
                Error::CODE::ERR_VALIDATION,
                R"(parsing error, request body must be json)"
            )
        ); 
    }
}

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateLoginReuest(const HTTPRequest& req) {
    try{
        return make_result(
            std::make_shared<LoginRequest>(
                json::parse(req.body).get<LoginRequest>()
            )
        );
    } catch (std::exception&) {
        return make_result(
            nullptr,
            std::make_shared<Error>(
                Error::CODE::ERR_VALIDATION,
                R"(parsing error, request body must be json)"
            )
        ); 
    }
}

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateLogoutReuest(const HTTPRequest& req){
    try{
        return make_result(
            std::make_shared<LogoutRequest>(
                json::parse(req.body).get<LogoutRequest>()
            )
        );
    } catch (std::exception&) {
        return make_result(
            nullptr,
            std::make_shared<Error>(
                Error::CODE::ERR_VALIDATION,
                R"(parsing error, request body must be json)"
            )
        ); 
    }
}

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateSearchReuest(const HTTPRequest& req) {
    try {
        auto jsonReq = json::parse(req.body);
        
        if(jsonReq.find("location") == jsonReq.end()) {
            return make_result(
                nullptr,
                std::make_shared<Error>(
                    Error::CODE::ERR_VALIDATION,
                    R"(missing required field "location")"
                )
            );
        }

        auto location = jsonReq["location"].get<std::string>();

        auto offsetIter = jsonReq.find("offset");
        auto offset = (offsetIter != jsonReq.end()) ? offsetIter->get<int>() : DEFAULT_SEARCH_OFFSET;

        auto limitIter = jsonReq.find("limit");
        auto limit = (limitIter != jsonReq.end()) ? limitIter->get<int>() : DEFAULT_SEARCH_LIMIT;

        return make_result(std::make_shared<SearchRequest>(location, offset, limit));

    } catch (std::exception&) {
        return make_result(
            nullptr,
            std::make_shared<Error>(
                Error::CODE::ERR_VALIDATION,
                R"(parsing error, request body must be json)"
            )
        ); 
    }
}

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateRegisterNotificationReuest(const HTTPRequest& req) {
    try{
        return make_result(
            std::make_shared<RegisterNotificationRequest>(
                json::parse(req.body).get<RegisterNotificationRequest>()
            )
        );
    } catch (std::exception&) {
        return make_result(
            nullptr,
            std::make_shared<Error>(
                Error::CODE::ERR_VALIDATION,
                R"(parsing error, request body must be json)"
            )
        ); 
    }
}

}