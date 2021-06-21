#include <mongo_repository.h>
#include <string>

namespace cta {



Result<std::shared_ptr<LocationInfo>> MongoRepository::GetLocationInfo(const std::string location) {

    return make_result(std::make_shared<LocationInfo>(), nullptr);
}

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetAllLocationInfo(int offset, int limit) {
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
}

std::shared_ptr<Error> MongoRepository::StoreSession(const std::string& email, const std::string& sessionID) {
    return nullptr;
}

std::shared_ptr<Error> MongoRepository::RemoveSession(const std::string& sessionID) {
    return nullptr;
}


// Should return ERR_NOTFOUND if session does not exist
Result<std::string> MongoRepository::GetEmailBySessionID(const std::string& sessionID) {
    return make_result(std::string{""}, nullptr);
}

Result<std::string> MongoRepository::GetPasswordHash(const std::string& email) {
    return make_result(std::string{""}, nullptr);
}

std::shared_ptr<Error> MongoRepository::RegisterNotification(const std::string& email, const std::string& location) {
    return nullptr;
}

Result<std::list<std::shared_ptr<LocationInfo>>> MongoRepository::GetUpdatedLocationInfoSince(time_t time) {
    return make_result(std::list<std::shared_ptr<LocationInfo>>{}, nullptr);
}

Result<time_t> MongoRepository::GetLastNotificationSentTime() {
    return make_result(time(nullptr), nullptr);
}

std::shared_ptr<Error> MongoRepository::UpdateLastNotificationSentTime() {
    return nullptr;
}

std::shared_ptr<Error> MongoRepository::CreateUser(const std::string& email, const std::string& password, const std::string& name) {
    return nullptr;
}

}
