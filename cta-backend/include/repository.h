/**
 * repository.h declars interface for repository - data store
 */

#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <memory>
#include <list>
#include <time.h>
#include <error/error.h>
#include <result.h>
#include <model/location_info.h>

namespace cta {

class Repository {

public:
    // TODO:  determine parameters 
    virtual Result<std::shared_ptr<LocationInfo>> GetLocationInfo() = 0;
    virtual std::shared_ptr<Error> StoreSession(const std::string& userID, const std::string& sessionID) = 0;
    virtual std::shared_ptr<Error> RemoveSession(const std::string& userID) = 0;
    virtual Result<std::string> GetPasswordHash(const std::string& userID) = 0;
    virtual std::shared_ptr<Error> RegisterNotification() = 0;
    virtual Result<std::list<std::shared_ptr<LocationInfo>>> GetUpdatedLocationInfoSince(time_t time) = 0;
    virtual Result<time_t> GetLastNotificationSentTime() = 0;
    virtual std::shared_ptr<Error> UpdateLastNotificationSentTime() = 0;
    // TODO:  determine parameters 
    virtual std::shared_ptr<Error> CreateUser() = 0;
};

}

#endif // __REPOSITORY_H__