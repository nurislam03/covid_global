#include <json/json.hpp>
#include <json_serializer.h>
#include <response/get_all_location_info_response.h>
#include <response/empty_response.h>
#include <response/login_response.h>
#include <response/search_response.h>
#include <model/location_info.h>


namespace cta {

using json = nlohmann::json;

void to_json(json &j, const std::shared_ptr<LocationInfo>& info) {
    j = json{
        // TODO: fill this when LocationInfo class is complete
    };
}

void to_json(json& j, const GetAllLocationInfoResponse& r) {
    j = json{
        {"info", r.info}
    };
}

void to_json(json& j, const LoginResponse& r) {
    j = json{
        {"sessionID", r.sessionID}
    };
}

void to_json(json& j, const SearchResponse& r) {
    j = json{
        {"info", r.info}
    };
}


std::string JsonSerializer::Serialize(const GetAllLocationInfoResponse& r) const {
    return json(r).get<std::string>();
}

std::string JsonSerializer::Serialize(const EmptyResponse&) const {
    return "";
}

std::string JsonSerializer::Serialize(const LoginResponse& r) const {
    return json(r).get<std::string>();
}

std::string JsonSerializer::Serialize(const SearchResponse& r) const {
    return json(r).get<std::string>();
}


}