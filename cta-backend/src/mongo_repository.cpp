#include <mongo_repository.h>
#include <string>

#include <iostream>

namespace cta {



Result<std::shared_ptr<LocationInfo>> MongoRepository::GetLocationInfo(const std::string location) {
    std::cout << "MongoRepository::GetLocationInfo is called\n";
    return make_result(std::make_shared<LocationInfo>(), nullptr);
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
Result<std::string> MongoRepository::GetEmailBySessionID(const std::string& sessionID) {
    std::cout << "MongoRepository::GetEmailBySessionID is called\n";
    return make_result(std::string{""}, nullptr);
}

Result<std::string> MongoRepository::GetPasswordHash(const std::string& email) {
    std::cout << "MongoRepository::GetPasswordHash is called\n";
    return make_result(std::string{""}, nullptr);
}

std::shared_ptr<Error> MongoRepository::RegisterNotification(const std::string& email, const std::string& location) {
    std::cout << "MongoRepository::RegisterNotification is called\n";
    return nullptr;
}

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetUpdatedLocationInfoSince(time_t time) {
    std::cout << "MongoRepository::GetUpdatedLocationInfoSince is called\n";
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
}

Result<time_t> MongoRepository::GetLastNotificationSentTime() {
    std::cout << "MongoRepository::GetLastNotificationSentTime is called\n";
    return make_result(time(nullptr), nullptr);
}

std::shared_ptr<Error> MongoRepository::UpdateLastNotificationSentTime() {
    std::cout << "MongoRepository::UpdateLastNotificationSentTime is called\n";
    return nullptr;
}

std::shared_ptr<Error> MongoRepository::CreateUser(const std::string& email, const std::string& password, const std::string& name) {
    std::cout << "MongoRepository::CreateUser is called\n";
    return nullptr;
}

Result<std::list<std::string>> MongoRepository::GetSubscriptionsByEmail(const std::string email) {
    std::cout << "MongoRepository::GetSubscriptionsByEmail is called\n";
    return make_result(std::list<std::string>{});
}

Result<std::string> MongoRepository::GetNameByEmail(const std::string& email) {
    std::cout << "MongoRepository::GetNameByEmail is called\n";
    return make_result("Jon Doe");
}

}
