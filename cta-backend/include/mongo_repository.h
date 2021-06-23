#ifndef __MONGO_REPOSITORY_H__
#define __MONGO_REPOSITORY_H__
#include <repository.h>

namespace cta {

class MongoRepository final : public Repository {
    Result<std::shared_ptr<LocationInfo>> GetLocationInfo(const std::string location) override;
    Result<std::list<std::shared_ptr<LocationInfo>>> GetAllLocationInfo(int offset = 0, int limit = 10) override;
    std::shared_ptr<Error> StoreSession(const std::string& email, const std::string& sessionID) override;
    std::shared_ptr<Error> RemoveSession(const std::string& sessionID) override;
    Result<std::string> GetEmailBySessionID(const std::string& sessionID) override;
    Result<std::string> GetPasswordHash(const std::string& userID) override;
    std::shared_ptr<Error> RegisterNotification(const std::string& email, const std::string& location) override;
    Result<std::list<std::shared_ptr<LocationInfo>>> GetUpdatedLocationInfoSince(time_t time) override;
    Result<time_t> GetLastNotificationSentTime() override;
    std::shared_ptr<Error> UpdateLastNotificationSentTime() override;
    std::shared_ptr<Error> CreateUser(const std::string& email, const std::string& password, const std::string& name) override;
    Result<std::list<std::string>> GetSubscriptionsByEmail(const std::string email);
    Result<std::string> GetNameByEmail(const std::string& email);
};


}
#endif // __MONGO_REPOSITORY_H__