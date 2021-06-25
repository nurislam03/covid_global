#include <cta_service.h>

using namespace std::literals;

namespace cta {

const auto SESSION_EXPIRY_DURATION = 15min;

CTAService::CTAService(std::shared_ptr<Repository> repo)
    : repo{repo} {}

Result<std::shared_ptr<ServiceResponse>> CTAService::Serve(const ServiceRequest& req) {
    return req.GetServed(*this);
}

Result<std::shared_ptr<SearchResponse>> CTAService::Search(const SearchRequest& req) {
    auto [info, err] = repo->GetLocationInfo(req.location);
    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    return make_result(std::make_shared<SearchResponse>(info), err);
}

Result<std::shared_ptr<EmptyResponse>> CTAService::RegisterNotification(const RegisterNotificationRequest& req){
    auto [email, err] =  repo->GetEmailBySessionID(req.sessionID, SESSION_EXPIRY_DURATION);

    if (err != nullptr) {
        if(err->getCode() == Error::CODE::ERR_NOTFOUND) {
            return make_result(nullptr, std::make_shared<Error>(
                Error::CODE::ERR_UNAUTHORIZED, "Invalid session"
            ));
        }

        return make_result(nullptr, err);
    }

    return make_result(
        std::make_shared<EmptyResponse>(),
        repo->RegisterNotification(email, req.location));
}

Result<std::shared_ptr<GetAllLocationInfoResponse>> CTAService::GetAllLocationInfo(const GetAllLocationInfoRequest& req) {
    auto [info, err] = repo->GetAllLocationInfo(req.offset, req.limit);
    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    return make_result(std::make_shared<GetAllLocationInfoResponse>(info), nullptr);
}

}
