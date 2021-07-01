#include <mongo_repository.h>
#include <string>

#include <iostream>
#include <cstdio>

#include <cstdint>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bson_serializer.h>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using mongocxx::query_exception;

using namespace bsoncxx::builder::basic;

namespace cta {


MongoRepository::MongoRepository(const std::string& connectionURL, const std::string& dbName)
    : uri(connectionURL), client(uri), db(client.database(dbName)) 
{
}

std::shared_ptr<MongoRepository> MongoRepository::Create(const std::string& connectionURL, const std::string& dbName) {
    static mongocxx::instance instance{}; // This should be done only once. Hence static
    static auto mongoRepo = std::shared_ptr<MongoRepository>(new MongoRepository(connectionURL, dbName));
    
    return mongoRepo;
}

bool MongoRepository::Ping() {
    bsoncxx::document::value command = make_document(kvp("ping", 1));
    auto res = db.run_command(command.view());

    return res.view()["ok"].get_int32() == 1;
}

Result<std::shared_ptr<LocationInfo>> MongoRepository::GetLocationInfo(const std::string& countryCode) {
    std::cout << "MongoRepository::GetLocationInfo is called\n";

    auto locInfoColl = db["location"];

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << "countryCode" << countryCode << bsoncxx::builder::stream::finalize;

    LocationInfo locInfo;

    try {
        auto result = locInfoColl.find_one(doc_value.view());
        if(!result) {
            return make_result(nullptr,
                std::make_shared<Error>(Error::CODE::ERR_NOTFOUND, "location not found"));
        }

        auto view = result->view();
        locInfo.Deserialize(BsonSerializer{}, std::addressof(view));
    } catch (const mongocxx::query_exception& e) {
        return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_REPO, e.what()));
    }

    return make_result(std::make_shared<LocationInfo>(locInfo), nullptr);
}


// FIXME: optimize this function, a lot of copying are happening here
Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetAllLocationInfo(int offset, int limit) {
    
    std::cout << "MongoRepository::GetAllLocationInfo is called\n";

        auto locInfoColl = db["location"];

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << bsoncxx::builder::stream::finalize;

    std::list<std::shared_ptr<LocationInfo>> locs{};

    try {
        auto cur = locInfoColl.find(
            doc_value.view(),
            mongocxx::options::find()
                .skip(offset)
                .limit(limit)
        );

        for (auto result : cur) {
            LocationInfo loc;
            loc.Deserialize(BsonSerializer{}, std::addressof(result));
            locs.push_back(std::make_shared<LocationInfo>(loc));
        }
    } catch (const mongocxx::query_exception& e) {
        return make_result(std::list<std::shared_ptr<LocationInfo>>{}, std::make_shared<Error>(Error::CODE::ERR_REPO, e.what()));
    }

    return make_result(locs, nullptr);
}

std::shared_ptr<Error> MongoRepository::StoreSession(const std::string& email, const std::string& sessionID) {
    std::cout << "MongoRepository::StoreSession is called\n";
    return nullptr;
}

std::shared_ptr<Error> MongoRepository::RemoveSession(const std::string& sessionID) {
    std::cout << "MongoRepository::RemoveSession is called\n";
    return nullptr;
}


// Should return ERR_NOTFOUND if session does not exist
Result<std::string> MongoRepository::GetEmailBySessionID(const std::string& sessionID, const chrono::duration<int> expiryDuration) {
    std::cout << "MongoRepository::GetEmailBySessionID is called\n";
    return make_result(std::string{""}, nullptr);
}

// Result<std::pair<std::string, int>> MongoRepository::GetPasswordHashAndFailedLoginAttemptCount(const std::string& email) {
//     std::cout << "MongoRepository::GetPasswordHashAndFailedLoginAttemptCount is called\n";
//     return make_result(std::make_pair(std::string{""}, 0), nullptr);
// }

std::shared_ptr<Error> MongoRepository::RegisterNotification(const std::string& email, const std::string& location) {
    std::cout << "MongoRepository::RegisterNotification is called\n";

    auto result = db["subscription_info"].insert_one(make_document(
            kvp("email", email),
            kvp("location", location)
    ));

    if (!result) {
        return std::make_shared<Error>(Error::CODE::ERR_REPO, "RegisterNotification failed");
    }

    return nullptr;
}

// TODO: UnregisterNotification 

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetUpdatedLocationInfoSince(time_t time) {
    std::cout << "MongoRepository::GetUpdatedLocationInfoSince is called\n";
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
}

Result<time_point> MongoRepository::GetLastNotificationSentTime() {
    std::cout << "MongoRepository::GetLastNotificationSentTime is called\n";

    auto result = db["notification_time_info"].find_one(make_document());
    if(!result) {
        return make_result(time_point(),std::make_shared<Error>(Error::CODE::ERR_REPO, "RegisterNotification failed"));
    }

    auto elem = result->view()["lastSentAt"];

    auto lastSentAt = elem ? elem.get_date() : time_point();

    return make_result(lastSentAt, nullptr);
}

std::shared_ptr<Error> MongoRepository::UpdateLastNotificationSentTime(time_point updateTime) {
    std::cout << "MongoRepository::UpdateLastNotificationSentTime is called\n";

    auto result = db["notification_time_info"].update_one(
        make_document(),
        make_document(kvp("lastSentAt", bsoncxx::types::b_date(updateTime)))
    );

    if(!result) {
        return std::make_shared<Error>(Error::CODE::ERR_REPO, "UpdateLastNotificationSentTime failed");
    }

    return nullptr;
}

std::shared_ptr<Error> MongoRepository::CreateUser(const std::string& email, const std::string& passwordHash, const std::string& name) {
    std::cout << "MongoRepository::CreateUser is called\n";

    auto userCollection = db.collection("user");

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << "email" << email
                << "passwordHash" << passwordHash
                << "name" << name << bsoncxx::builder::stream::finalize;

    auto result = userCollection.insert_one(doc_value.view());

    if (result) {
        std::cout << "user created with ID: " << result->inserted_id().get_oid().value.to_string() << std::endl;
        return nullptr;
    }

    return std::make_shared<Error>(Error::CODE::ERR_UNKNOWN, "Create user failed");
}

Result<std::list<std::string>> MongoRepository::GetSubscriptionsByEmail(const std::string email) {
    std::cout << "MongoRepository::GetSubscriptionsByEmail is called\n";

    auto subscriptionCollection = db.collection("subscription_info");

    mongocxx::pipeline p{};
    p.match(make_document(
        kvp("email", "abc@email.com")
    ));
    p.group(make_document(
        kvp("_id", "$email"),
        kvp("locations", make_document(kvp("$addToSet", "$location")))
    ));
    p.project(make_document(
        kvp("_id", 0),
        kvp("locations", 1)
    ));
    auto cursor = subscriptionCollection.aggregate(p, mongocxx::options::aggregate{});

    if (cursor.begin() == cursor.end()) {
        std::cout << "No Subscription found" << std::endl;
        return make_result(std::list<std::string>{});
    }
    auto result_array = (*cursor.begin())["locations"].get_array();

    std:: list <std::string> result_list;

    for(auto r : result_array.value) {
        result_list.push_back(r.get_value().get_utf8().value.to_string());
    }

    return make_result(result_list);
}

Result<std::string> MongoRepository::GetNameByEmail(const std::string& email) {
    std::cout << "MongoRepository::GetNameByEmail is called\n";

    auto userCollection = db.collection("user");

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << "email" << email << bsoncxx::builder::stream::finalize;

    auto result = userCollection.find_one(doc_value.view()); 

    if (result) {
        std::cout << "Email already registered: " << bsoncxx::to_json(*result) << std::endl;
        // return make_result(*result.name);
    }

    return make_result("Jon Doe"); // todo: handle error
}

Result<bool> MongoRepository::IsEmailAlreadyRegistered(const std::string& email) {
    std::cout << "MongoRepository::IsEmailAlreadyRegistered is called\n";

    auto userCollection = db.collection("user");

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << "email" << email << bsoncxx::builder::stream::finalize;

    auto result = userCollection.find_one(doc_value.view()); 

    if (result) {
        std::cout << "Email already registered: " << bsoncxx::to_json(*result) << std::endl;
        return make_result(true);
    }
    return make_result(false);
}

std::shared_ptr<Error> MongoRepository::IncrementFailedLoginAttempt(const std::string& email) {
    std::cout << "MongoRepository::IncrementFailedLoginAttempt is called\n";
    using bsoncxx::builder::basic::kvp;

    auto result = db["user"].update_one(
        make_document(kvp("email", email)),
        make_document(kvp("$inc", make_document(kvp(
            "failedLoginAttemptCount", 1
        ))))
    );

    if (!result) {
        return std::make_shared<Error>(Error::CODE::ERR_REPO, "IncrementFailedLoginAttempt failed");
    }

    return nullptr;
}

std::shared_ptr<Error> MongoRepository::ResetFailedLoginAttempt(const std::string& email) {
    std::cout << "MongoRepository::ResetFailedLoginAttempt is called\n";

    using bsoncxx::builder::basic::kvp;

    auto result = db["user"].update_one(
        make_document(kvp("email", email)),
        make_document(kvp("$set", make_document(kvp(
            "failedLoginAttemptCount", 0
        ))))
    );

    if (!result) {
        return std::make_shared<Error>(Error::CODE::ERR_REPO, "ResetFailedLoginAttempt failed");
    }

    return nullptr;
}

Result<std::shared_ptr<User>> MongoRepository::GetUser(const std::string& email) const {
    std::cout << "MongoRepository::GetUser is called\n";

    // TODO: get this from db
    bsoncxx::builder::stream::document builder{};
    auto queryDoc = builder
        << "email" << email << bsoncxx::builder::stream::finalize;

    auto result = db["user"].find_one(queryDoc.view());
    if(!result) {
        return make_result(nullptr, std::make_shared<Error>(
            Error::CODE::ERR_NOTFOUND,
            "User not found"
        ));
    }
    
    User user;
    auto view = result->view();
    auto err = user.Deserialize(BsonSerializer{}, std::addressof(view));

    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    return make_result(std::make_shared<User>(user));
}

}
