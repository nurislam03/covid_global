/**
 * cat_service define interface for Corona Travel Assistance (cta) service
 * 
 */

#include <error/error.h>
#include <request.h>

namespace cta {

class ICTAService {
    virtual Error getRestrictionUpdate(const GetRestrictionUpdateRequest& gruReq) = 0;
};

}