/**
 * cat_service define interface for Corona Travel Assistance (cta) service
 * 
 */

#ifndef __CTA_SERVICE_H__
#define __CTA_SERVICE_H__

#include <error/error.h>
#include <service.h>
#include <request/search_request.h>
#include <request/register_notification_request.h>
#include <request/get_all_location_info_request.h>
#include <request/notify_request.h>
#include <repository.h>
#include <response/service_response.h>
#include <response/search_response.h>
#include <response/get_all_location_info_response.h>
#include <response/empty_response.h>
#include <notifier.h>

namespace cta {

class CTAService final : public Service  {
    friend class SearchRequest;
    friend class RegisterNotificationRequest;
    friend class GetAllLocationInfoRequest;
    friend class NotifyRequest;

    std::shared_ptr<Repository> repo;
    std::shared_ptr<Notifier> notifier;
    std::string frontEndCountryDetailsURL;

public:

    CTAService(std::shared_ptr<Repository> repo, std::shared_ptr<Notifier> notifier, const std::string& frontEndCountryDetailsURL);

    Result<std::shared_ptr<ServiceResponse>> Serve(const ServiceRequest& req) override;

private:
    Result<std::shared_ptr<SearchResponse>> Search(const SearchRequest& req);
    Result<std::shared_ptr<EmptyResponse>> RegisterNotification(const RegisterNotificationRequest& req);
    Result<std::shared_ptr<GetAllLocationInfoResponse>> GetAllLocationInfo(const GetAllLocationInfoRequest& req);
    Result<std::shared_ptr<EmptyResponse>> NotifySubscriber(const NotifyRequest& req);
};

}

#endif // __CTA_SERVICE_H__