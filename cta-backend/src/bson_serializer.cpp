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
        dst = LocationInfo{ docView["countryCode"].get_utf8().value.to_string() };
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