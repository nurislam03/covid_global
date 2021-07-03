#include <cta_service.h>
#include <iostream>

using namespace std::literals;

namespace cta {

const auto SESSION_EXPIRY_DURATION = 15min;

CTAService::CTAService(std::shared_ptr<Repository> repo, std::shared_ptr<Notifier> notifier, const std::string& frontEndCountryDetailsURL)
    : repo{repo}, notifier{notifier}, frontEndCountryDetailsURL{frontEndCountryDetailsURL} {}

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

Result<std::shared_ptr<EmptyResponse>> CTAService::NotifySubscriber(const NotifyRequest&) {
    using time_point = std::chrono::system_clock::time_point;

    auto [lastSentTime, err] = repo->GetLastNotificationSentTime();
    if(err) {
        return make_result(nullptr, err);
    }

    auto [updatedCountries, err1] = repo->GetUpdatedCountryCodeSince(lastSentTime);
    if(err1) {
        return make_result(nullptr, err);
    }

    for(const auto& country : updatedCountries) {
        auto [subscribers, err] = repo->GetSubscriptionEmailsByLocation(country);
        if(err) {
            std::cout << "error getting subscriber list for " << country << std::endl;
            continue;
        }

        if(subscribers.size() == 0) continue;

        auto URL = frontEndCountryDetailsURL + "/" + country;
        auto subj = "Corona Travel Assistant update for " + country;
        auto body = "The travel status for " + country + " been updated, please visit "
            + URL + "to get the updated information";

        err = notifier->SendNotification(subscribers, subj, body);
        if (err) {
            std::cout << "error notifying subscriber list for " << country << std::endl;
            continue;
        }
    }

    err = repo->UpdateLastNotificationSentTime(std::chrono::system_clock::now());
    
    return make_result(std::make_shared<EmptyResponse>(), err);
}

}
