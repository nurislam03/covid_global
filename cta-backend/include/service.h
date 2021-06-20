#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <error/error.h>
#include <request/service_request.h>
#include <response/service_response.h>

namespace cta {

class Service {
public:
    virtual Result<std::shared_ptr<ServiceResponse>> Serve(const ServiceRequest& req) = 0;
};

}

#endif //__SERVICE_H__