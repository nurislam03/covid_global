/**
 * cat_service define interface for Corona Travel Assistance (cta) service
 * 
 */

#ifndef __CTA_SERVICE_H__
#define __CTA_SERVICE_H__

#include <error/error.h>
#include <service.h>
#include <request/search_request.h>

namespace cta {

class CTAService final : public Service  {
    friend class SearchRequest;

public:
    Error* Serve(const ServiceRequest& req) override;

private:
    Error* Search(const SearchRequest& req);
};

}

#endif // __CTA_SERVICE_H__