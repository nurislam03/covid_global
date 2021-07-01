#include <bson_serializer.h>
#include <model/location_info.h>
#include <model/session_info.h>
#include <model/subscription_info.h>
#include <model/user.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/document/element.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <chrono>

namespace cta {

template <typename T>
T getValue(bsoncxx::document::view& docView, const std::string& fieldName) {
    //static_assert(false, "implementation not provided");
    return std::declval<T>();
}

template <>
std::string getValue<std::string>(bsoncxx::document::view& docView, const std::string& fieldName) {
    auto elem = docView[fieldName];
    return elem ? elem.get_utf8().value.to_string() : "";
}

template <>
int getValue<int>(bsoncxx::document::view& docView, const std::string& fieldName) {
    auto elem = docView[fieldName];
    return elem ? static_cast<int>(elem.get_int32()) : -1;
}

template <>
std::chrono::system_clock::time_point getValue<std::chrono::system_clock::time_point>(bsoncxx::document::view& docView, const std::string& fieldName) {
    auto elem = docView[fieldName];
    return elem 
        ? elem.get_date()
        : std::chrono::system_clock::time_point();
}

std::shared_ptr<Error> BsonSerializer::Deserialize(LocationInfo& dst, void* src) const {
    auto docView = *static_cast<bsoncxx::document::view*>(src);

    try {
        dst.countryCode = getValue<std::string>(docView, "countryCode"); 
        dst.countryName = getValue<std::string>(docView, "countryName");
        dst.stateName = getValue<std::string>(docView, "stateName");
        dst.citizenNntry = getValue<std::string>(docView, "citizenNntry");
        dst.foreignersEntry = getValue<std::string>(docView, "foreignersEntry");
        dst.tourismStatus = getValue<std::string>(docView, "tourismStatus");
        dst.quarantineStatus = getValue<std::string>(docView, "quarantineStatus");
        dst.lockdownStatus = getValue<std::string>(docView, "lockdownStatus");
        dst.breakingNews = getValue<std::string>(docView, "breakingNews");
        dst.airlinesUpdate = getValue<std::string>(docView, "airlinesUpdate");
        dst.entryPolicyForeigners = getValue<std::string>(docView, "entryPolicyForeigners");
        dst.entryPolicyCitizen = getValue<std::string>(docView, "entryPolicyCitizen");
        dst.quarantinePolicyForeigners = getValue<std::string>(docView, "quarantinePolicyForeigners");
        dst.quarantinePolicyCitizen = getValue<std::string>(docView, "quarantinePolicyCitizen");
        dst.certificationForeigners = getValue<std::string>(docView, "certificationForeigners");
        dst.certificationCitizen = getValue<std::string>(docView, "certificationCitizen");
        dst.travelRegulationRestriction = getValue<std::string>(docView, "travelRegulationRestriction");
        dst.flightRegulationRestriction = getValue<std::string>(docView, "flightRegulationRestriction");
        dst.zoneStatus = getValue<std::string>(docView, "zoneStatus");
        dst.totalCase = getValue<int>(docView, "totalCase");
        dst.newCase = getValue<int>(docView, "newCase");
        dst.activeCase = getValue<int>(docView, "activeCase");
        dst.criticalCase = getValue<int>(docView, "criticalCase");
        dst.totalDeaths = getValue<int>(docView, "totalDeaths");
        dst.newDeath = getValue<int>(docView, "newDeath");
        dst.createdDate = getValue<std::chrono::system_clock::time_point>(docView, "createdDate");
        dst.updatedDate = getValue<std::chrono::system_clock::time_point>(docView, "updatedDate");
    } catch (const bsoncxx::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(User& dst, void* src) const {
    auto docView = *static_cast<bsoncxx::document::view*>(src);

    try {
        dst = User{
            getValue<std::string>(docView, "name"),
            getValue<std::string>(docView, "email"),
            getValue<std::string>(docView, "passwordHash"),
            getValue<int>(docView, "failedLoginAttemptCount")
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(SessionInfo& dst, void* src) const {
    auto docView = *static_cast<bsoncxx::document::view*>(src);

    try {
        dst = SessionInfo{
            getValue<std::string>(docView, "sessionID"),
            getValue<std::string>(docView, "email"),
            getValue<std::chrono::system_clock::time_point>(docView, "createdAt")
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(SubscriptionInfo& dst, void* src) const {
    auto docView = *static_cast<bsoncxx::document::view*>(src);

    try {
        dst = SubscriptionInfo{
            getValue<std::string>(docView, "email"),
            getValue<std::string>(docView, "location")
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

}
