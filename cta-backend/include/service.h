#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <error/error.h>
#include <request/service_request.h>

namespace cta {

class Service {
    virtual Error* Serve(const ServiceRequest& req) = 0;
};

}

#endif //__SERVICE_H__