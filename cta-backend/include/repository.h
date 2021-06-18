/**
 * repository.h declars interface for repository - data store
 */

#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <memory>
#include <error/error.h>

namespace cta {

class Repository {

public:
    // TODO:  determine parameters 
    virtual std::shared_ptr<Error> GetRestrictionUpdate() = 0;
    virtual std::shared_ptr<Error> StoreSession(const std::string& userID, const std::string& sessionID) = 0;
    virtual std::shared_ptr<Error> CheckCredential(const std::string& userID, const std::string& pwHash) = 0;
    // TODO:  determine parameters 
    virtual std::shared_ptr<Error> CreateUser() = 0;
};

}

#endif // __REPOSITORY_H__