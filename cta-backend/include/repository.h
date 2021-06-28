/**
 * repository.h declars interface for repository - data store
 */

#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <memory>
#include <list>
#include <ctime>
#include <error/error.h>
#include <result.h>
#include <model/location_info.h>
#include <model/user.h>
#include <model/subscription_info.h>
#include <model/session_info.h>
#include <chrono>
#include <def.h>


namespace cta {

class Repository {

public:
    virtual Result<std::shared_ptr<LocationInfo>> GetLocationInfo(const std::string location) = 0;
    virtual Result<std::list<std::shared_ptr<LocationInfo>>> GetAllLocationInfo(int offset = 0, int limit = 10) = 0;
    virtual std::shared_ptr<Error> StoreSession(const std::string& email, const std::string& sessionID) = 0;
    virtual std::shared_ptr<Error> RemoveSession(const std::string& sessionID) = 0;
    virtual Result<std::string> GetEmailBySessionID(const std::string& sessionID, const duration expiryDuration) = 0;
    virtual Result<std::pair<std::string, int>> GetPasswordHashAndFailedLoginAttemptCount(const std::string& email) = 0;
    virtual std::shared_ptr<Error> RegisterNotification(const std::string& email, const std::string& location) = 0;
    virtual Result<std::list<std::shared_ptr<LocationInfo>>> GetUpdatedLocationInfoSince(time_t time) = 0;
    virtual Result<time_point> GetLastNotificationSentTime() = 0;
    virtual std::shared_ptr<Error> UpdateLastNotificationSentTime() = 0;
    virtual std::shared_ptr<Error> CreateUser(const std::string& email, const std::string& password, const std::string& name) = 0;
    virtual Result<std::list<std::string>> GetSubscriptionsByEmail(const std::string email) = 0;
    virtual Result<std::string> GetNameByEmail(const std::string& email) = 0;
    virtual Result<bool> IsEmailAlreadyRegistered(const std::string& email) = 0;
    virtual std::shared_ptr<Error> IncrementFailedLoginAttempt(const std::string& email) = 0;
    virtual std::shared_ptr<Error> ResetFailedLoginAttempt(const std::string& email) = 0;

    virtual Result<std::shared_ptr<User>> GetUser(const std::string& email) const = 0;
};

}

#endif // __REPOSITORY_H__