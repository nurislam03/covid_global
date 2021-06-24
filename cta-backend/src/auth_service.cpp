#include <auth_service.h>

namespace cta {

std::string gen_random_id() {
    // TODO: implement
    return "";
}

std::string get_hash(const std::string& str) {
    // TODO: implement
    return str;
}

AuthService::AuthService(std::shared_ptr<Repository> repo)
    : repo{repo} {}

Result<std::shared_ptr<ServiceResponse>> AuthService::Serve(const ServiceRequest& req) {
    return req.GetServed(*this);
}

Result<std::shared_ptr<EmptyResponse>> AuthService::Register(const RegistrationRequest& req){
    return make_result(
        std::make_shared<EmptyResponse>(),
        repo->CreateUser(req.email, get_hash(req.password), req.name));
}

Result<std::shared_ptr<LoginResponse>> AuthService::Login(const LoginRequest& req) {
    auto [hash, err] = repo->GetPasswordHash(req.email);

    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    if (hash != get_hash(req.password)) {
        return make_result(nullptr, std::make_shared<Error>(
            Error::CODE::ERR_WRONG_PASSWORD,
            "Incorrect password"));
    }

    auto sessionID = gen_random_id();
    err = repo->StoreSession(req.email, sessionID);
    if (err != nullptr) {
        // TODO: log error
        return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_REPO, "Internal Server"));
    }

    auto [name, err2] = repo->GetNameByEmail(req.email);
    if (err != nullptr) {
        // TODO: log error
        return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_REPO, "Internal Server"));
    }

    auto [subscriptions, err3] = repo->GetSubscriptionsByEmail(req.email);
    if (err != nullptr) {
        // TODO: log error
        return make_result(nullptr, std::make_shared<Error>(Error::CODE::ERR_REPO, "Internal Server"));
    }

    return make_result(std::make_shared<LoginResponse>(name, req.email, sessionID, std::move(subscriptions)));
}

Result<std::shared_ptr<EmptyResponse>> AuthService::Logout(const LogoutRequest& req) {
    return make_result(
        std::make_shared<EmptyResponse>(),
        repo->RemoveSession(req.sessionID));
}

}
