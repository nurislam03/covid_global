#include <cta_service.h>

namespace cta {

Error* CTAService::Serve(const ServiceRequest& req) {
    return req.GetServed(*this);
}

Error* CTAService::Search(const SearchRequest& req) {
    return nullptr;
}

Error* CTAService::RegisterNotification(const RegisterNotificationRequest& req){
    return nullptr;
}

}
