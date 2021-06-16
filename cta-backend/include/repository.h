/**
 * repository.h declars interface for repository - data store
 */

#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <error/error.h>

namespace cta {

class IRepository {
    virtual Error getRestrictionUpdate() = 0;
};

}

#endif // __REPOSITORY_H__