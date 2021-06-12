/**
 * repository.h declars interface for repository - data store
 */

#include <error/error.h>
#include <request.h>

namespace cta {

class IRepository {
    virtual Error getRestrictionUpdate(const GetRestrictionUpdateRequest& gruReq) = 0;
};

}