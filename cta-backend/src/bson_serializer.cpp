#include <bson_serializer.h>
#include <model/location_info.h>
#include <model/session_info.h>
#include <model/subscription_info.h>
#include <model/user.h>
#include <bsoncxx/builder/stream/document.hpp>

namespace stream = bsoncxx::builder::stream;
using document = bsoncxx::document::value;

namespace cta {

std::shared_ptr<Error> BsonSerializer::Deserialize(LocationInfo& dst, void* src) const {
    auto docView = static_cast<document*>(src)->view();

    try {
        dst.countryCode = docView["countryCode"].get_utf8().value.to_string(); 
        dst.countryName = docView["countryName"].get_utf8().value.to_string(); 
        dst.stateName = docView["stateName"].get_utf8().value.to_string(); 
        dst.citizenNntry = docView["citizenNntry"].get_utf8().value.to_string(); 
        dst.foreignersEntry = docView["foreignersEntry"].get_utf8().value.to_string(); 
        dst.tourismStatus = docView["tourismStatus"].get_utf8().value.to_string(); 
        dst.quarantineStatus = docView["quarantineStatus"].get_utf8().value.to_string(); 
        dst.lockdownStatus = docView["lockdownStatus"].get_utf8().value.to_string(); 
        dst.breakingNews = docView["breakingNews"].get_utf8().value.to_string(); 
        dst.airlinesUpdate = docView["airlinesUpdate"].get_utf8().value.to_string(); 
        dst.entryPolicyForeigners = docView["entryPolicyForeigners"].get_utf8().value.to_string(); 
        dst.entryPolicyCitizen = docView["entryPolicyCitizen"].get_utf8().value.to_string(); 
        dst.quarantinePolicyForeigners = docView["quarantinePolicyForeigners"].get_utf8().value.to_string(); 
        dst.quarantinePolicyCitizen = docView["quarantinePolicyCitizen"].get_utf8().value.to_string(); 
        dst.certificationForeigners = docView["certificationForeigners"].get_utf8().value.to_string(); 
        dst.certificationCitizen = docView["certificationCitizen"].get_utf8().value.to_string(); 
        dst.travelRegulationRestriction = docView["travelRegulationRestriction"].get_utf8().value.to_string(); 
        dst.flightRegulationRestriction = docView["flightRegulationRestriction"].get_utf8().value.to_string(); 
        dst.zoneStatus = docView["zoneStatus"].get_utf8().value.to_string();
        dst.totalCase = static_cast<int>(docView["totalCase"].get_int32());
        dst.newCase = static_cast<int>(docView["newCase"].get_int32());
        dst.activeCase = static_cast<int>(docView["activeCase"].get_int32());
        dst.criticalCase = static_cast<int>(docView["criticalCase"].get_int32());
        dst.totalDeaths = static_cast<int>(docView["totalDeaths"].get_int32());
        dst.newDeath = static_cast<int>(docView["newDeath"].get_int32());
        dst.createdDate = docView["createdDate"].get_date();
        dst.updatedDate = docView["updatedDate"].get_date();
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(User& dst, void* src) const {
    auto docView = static_cast<document*>(src)->view();

    try {
        dst = User{
            docView["name"].get_utf8().value.to_string(),
            docView["email"].get_utf8().value.to_string(),
            docView["passwordHash"].get_utf8().value.to_string(),
            static_cast<int>(docView["failedLoginAttemptCount"].get_int32())
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(SessionInfo& dst, void* src) const {
    auto docView = static_cast<document*>(src)->view();

    try {
        dst = SessionInfo{
            docView["sessionID"].get_utf8().value.to_string(),
            docView["email"].get_utf8().value.to_string(),
            docView["created_at"].get_date()
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Error> BsonSerializer::Deserialize(SubscriptionInfo& dst, void* src) const {
    auto docView = static_cast<document*>(src)->view();

    try {
        dst = SubscriptionInfo{
            docView["email"].get_utf8().value.to_string(),
            docView["location"].get_utf8().value.to_string(),
        };
    } catch (const std::exception& e) {
        return std::make_shared<Error>(Error::CODE::ERR_PARSE, e.what());
    }
    
    return nullptr;
}

}