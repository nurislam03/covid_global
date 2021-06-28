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

Result<std::shared_ptr<LocationInfo>> MongoRepository::GetLocationInfo(const std::string location) {
    std::cout << "MongoRepository::GetLocationInfo is called\n";
    return make_result(std::make_shared<LocationInfo>("BGD"), nullptr);
}

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetAllLocationInfo(int offset, int limit) {
    
    std::cout << "MongoRepository::GetAllLocationInfo is called\n";
    
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
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

Result<std::pair<std::string, int>> MongoRepository::GetPasswordHashAndFailedLoginAttemptCount(const std::string& email) {
    std::cout << "MongoRepository::GetPasswordHashAndFailedLoginAttemptCount is called\n";
    return make_result(std::make_pair(std::string{""}, 0), nullptr);
}

std::shared_ptr<Error> MongoRepository::RegisterNotification(const std::string& email, const std::string& location) {
    std::cout << "MongoRepository::RegisterNotification is called\n";
    return nullptr;
}

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetUpdatedLocationInfoSince(time_t time) {
    std::cout << "MongoRepository::GetUpdatedLocationInfoSince is called\n";
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
}

Result<time_point> MongoRepository::GetLastNotificationSentTime() {
    std::cout << "MongoRepository::GetLastNotificationSentTime is called\n";
    return make_result(chrono::system_clock::now(), nullptr);
}

std::shared_ptr<Error> MongoRepository::UpdateLastNotificationSentTime() {
    std::cout << "MongoRepository::UpdateLastNotificationSentTime is called\n";
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
    return make_result(std::list<std::string>{});
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
        return make_result(result->name);
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
        return true;
    }
    return make_result(false);
}

std::shared_ptr<Error> MongoRepository::IncrementFailedLoginAttempt(const std::string& email) {
    std::cout << "MongoRepository::IncrementFailedLoginAttempt is called\n";
    return nullptr;
}

std::shared_ptr<Error> MongoRepository::ResetFailedLoginAttempt(const std::string& email) {
    std::cout << "MongoRepository::ResetFailedLoginAttempt is called\n";
    return nullptr;
}

Result<std::shared_ptr<User>> MongoRepository::GetUser(const std::string& email) const {
    std::cout << "MongoRepository::GetUser is called\n";

    // TODO: get this from db
    bsoncxx::builder::stream::document builder{};
    auto doc = builder
        << "name" << "Bighead"
        << "email" << "mail@bighead.me"
        << "passwordHash" << "password"
        << "failedLoginAttemptCount" << 0 << bsoncxx::builder::stream::finalize;
    
    auto err = User().Deserialize(BsonSerializer{}, static_cast<void*>(&doc));
    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    return make_result(std::make_shared<User>());
}

}
