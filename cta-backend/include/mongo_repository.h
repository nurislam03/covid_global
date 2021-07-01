#ifndef __MONGO_REPOSITORY_H__
#define __MONGO_REPOSITORY_H__
#include <repository.h>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>

namespace cta {

class MongoRepository final : public Repository {

    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;

    // std::shared_ptr<mongocxx::client> client;

    MongoRepository(const std::string& connectionURL, const std::string& dbName);
public:

    static std::shared_ptr<MongoRepository> Create(const std::string& connectionURL, const std::string& dbName);
    bool Ping();

    Result<std::shared_ptr<LocationInfo>> GetLocationInfo(const std::string& location) override;
    Result<std::list<std::shared_ptr<LocationInfo>>> GetAllLocationInfo(int offset = 0, int limit = 10) override;
    std::shared_ptr<Error> StoreSession(const std::string& email, const std::string& sessionID) override;
    std::shared_ptr<Error> RemoveSession(const std::string& sessionID) override;
    Result<std::string> GetEmailBySessionID(const std::string& sessionID, const chrono::duration<int> expiryDuration) override;
    // Result<std::pair<std::string, int>> GetPasswordHashAndFailedLoginAttemptCount(const std::string& userID) override;
    std::shared_ptr<Error> RegisterNotification(const std::string& email, const std::string& location) override;
    Result<std::list<std::shared_ptr<LocationInfo>>> GetUpdatedLocationInfoSince(time_t time) override;
    Result<time_point> GetLastNotificationSentTime() override;
    std::shared_ptr<Error> UpdateLastNotificationSentTime(time_point updateTime) override;
    std::shared_ptr<Error> CreateUser(const std::string& email, const std::string& password, const std::string& name) override;
    Result<std::list<std::string>> GetSubscriptionsByEmail(const std::string email) override;
    Result<std::string> GetNameByEmail(const std::string& email) override;
    Result<bool> IsEmailAlreadyRegistered(const std::string& email) override;
    std::shared_ptr<Error> IncrementFailedLoginAttempt(const std::string& email) override;
    std::shared_ptr<Error> ResetFailedLoginAttempt(const std::string& email) override;

    Result<std::shared_ptr<User>> GetUser(const std::string& email) const override;
};

}
#endif // __MONGO_REPOSITORY_H__