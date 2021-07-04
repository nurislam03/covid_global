#include <json/json.hpp>
#include <json_serializer.h>
#include <response/get_all_location_info_response.h>
#include <response/empty_response.h>
#include <response/login_response.h>
#include <response/search_response.h>
#include <model/location_info.h>
#include <date/date.h>


namespace cta {

using json = nlohmann::json;

void to_json(json &j, const std::shared_ptr<LocationInfo>& r) {

    using namespace date;

    j = json{
        {"countryCode", r->countryCode},
        {"countryName", r->countryName},
        {"stateName", r->stateName},
        {"detailsStatus", json{
            {"citizenNntry", r->citizenNntry},
            {"foreignersEntry", r->foreignersEntry},
            {"breakingNews", r->breakingNews},
            {"airlinesUpdate", r->airlinesUpdate},
            {"entryPolicyForeigners", r->entryPolicyForeigners},
            {"entryPolicyCitizen", r->entryPolicyCitizen},
            {"quarantinePolicyForeigners", r->quarantinePolicyForeigners},
            {"quarantinePolicyCitizen", r->quarantinePolicyCitizen},
            {"certificationForeigners", r->certificationForeigners},
            {"certificationCitizen", r->certificationCitizen},
            {"travelRegulationRestriction", r->travelRegulationRestriction},
            {"flightRegulationRestriction", r->flightRegulationRestriction}
        }},
        {"stats", json{
            {"totalCase", r->totalCase},
            {"newCase", r->newCase},
            {"activeCase", r->activeCase},
            {"criticalCase", r->criticalCase},
            {"totalDeaths", r->totalDeaths},
            {"newDeath", r->newDeath},
            {"zoneStatus", r->zoneStatus}
        }},
        {"status", json{
            {"tourismStatus", r->tourismStatus},
            {"quarantineStatus", r->quarantineStatus},
            {"lockdownStatus", r->lockdownStatus}
        }},
        {"createdDate", format("%D %T %Z", floor<std::chrono::milliseconds>(r->createdDate))},
        {"updatedDate", format("%D %T %Z", floor<std::chrono::milliseconds>(r->updatedDate))}
    };
}

void to_json(json& j, const GetAllLocationInfoResponse& r) {
    j = json{
        {"info", r.info}
    };
}

void to_json(json& j, const LoginResponse& r) {
    j = json{
        {"name", r.name},
        {"email", r.email},
        {"sessionID", r.sessionID},
        {"subscriptions", r.subscriptions}
    };
}

void to_json(json& j, const SearchResponse& r) {
    j = json{
        {"info", r.info}
    };
}


std::string JsonSerializer::Serialize(const GetAllLocationInfoResponse& r) const {
    return json(r).dump();
}

std::string JsonSerializer::Serialize(const EmptyResponse&) const {
    return "";
}

std::string JsonSerializer::Serialize(const LoginResponse& r) const {
    return json(r).dump();
}

std::string JsonSerializer::Serialize(const SearchResponse& r) const {
    return json(r).dump();
}

}