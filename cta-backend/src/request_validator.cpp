#include <request_validator.h>
#include <request/registration_request.h>
#include <request/login_request.h>
#include <request/logout_request.h>
#include <request/search_request.h>
#include <request/register_notification_request.h>
#include <request/get_all_location_info_request.h>
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

void from_json(const json& j, GetAllLocationInfoRequest& r) {
    j.at("offset").get_to(r.offset);
    j.at("limit").get_to(r.limit);
}

void from_json(const json& j, SearchRequest& sr) {
    j.at("location").get_to(sr.location);
}

// -----------------------------

Result<std::shared_ptr<ServiceRequest>>
RequestValidator::ValidateRequest(TYPE type, const HTTPRequest& req) {
    switch (type)
    {
    case TYPE::Registration:
        return Validate<RegistrationRequest>(req);
    case TYPE::Login:
        return Validate<LoginRequest>(req);
    case TYPE::Logout:
        return Validate<LogoutRequest>(req);
    case TYPE::Search:
        return Validate<SearchRequest>(req);
    case TYPE::RegisterNotification:
        return Validate<RegisterNotificationRequest>(req);
    case TYPE::GetAllLocationInfo:
        return Validate<GetAllLocationInfoRequest>(req);
    }

    // it is unlikely to reach here, but keeping it to make the compiler shut up about the retrun statement
    return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_UNKNOWN, "Unknown request"));
}

}