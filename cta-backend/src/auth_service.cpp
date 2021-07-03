#include <auth_service.h>
#include <ctime>
#include <unistd.h>
#include <hash/picosha2.h>

#include <iostream>

namespace cta {

const int MAX_FAILED_LOGIN_ATTEMPT = 3;

std::string gen_random(const int len) {
 
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
 
    srand( (unsigned) time(NULL) * getpid());
 
    tmp_s.reserve(len);
 
    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
 
    return tmp_s;
}

std::string gen_random_id() {
    return gen_random(12);
}

std::string get_hash(const std::string& str) {
    return picosha2::hash256_hex_string(str);
}

AuthService::AuthService(std::shared_ptr<Repository> repo)
    : repo{repo} {}

Result<std::shared_ptr<ServiceResponse>> AuthService::Serve(const ServiceRequest& req) {
    return req.GetServed(*this);
}

Result<std::shared_ptr<EmptyResponse>> AuthService::Register(const RegistrationRequest& req) {

    auto [res, err] = repo->IsEmailAlreadyRegistered(req.email);
    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    if(res) {
        return make_result(nullptr, std::make_shared<Error>(
            Error::CODE::ERR_DUPLICATE_USER,
            "Another user exists with this email"
        ));
    }

    return make_result(
        std::make_shared<EmptyResponse>(),
        repo->CreateUser(req.email, get_hash(req.password), req.name)
    );
}

Result<std::shared_ptr<LoginResponse>> AuthService::Login(const LoginRequest& req) {
    auto [userPtr, err] = repo->GetUser(req.email);

    if (err != nullptr) {
        return make_result(nullptr, err);
    }

    auto [name, email, hash, failedcount] = *userPtr;
    if (failedcount >= MAX_FAILED_LOGIN_ATTEMPT) {
        return make_result(nullptr, std::make_shared<Error>(
            Error::CODE::ERR_BLOCKED,
            "User is blocked")); 
    }

    if (hash != get_hash(req.password)) {
        repo->IncrementFailedLoginAttempt(email);
        return make_result(nullptr, std::make_shared<Error>(
            Error::CODE::ERR_WRONG_PASSWORD,
            "Incorrect password"));
    }

    auto sessionID = gen_random_id();
    err = repo->StoreSession(req.email, sessionID);
    if (err != nullptr) {
        // TODO: log error
        return make_result(nullptr, std::make_shared<Error>(err->getCode(), "Internal Server Error"));
    }

    auto [subscriptions, err2] = repo->GetSubscriptionsByEmail(req.email);
    if (err2 != nullptr) {
        // TODO: log error
        return make_result(nullptr, std::make_shared<Error>(err2->getCode(), "Internal Server Error"));
    }

    if(failedcount) {
        auto err3 = repo->ResetFailedLoginAttempt(email);
        if (err3 != nullptr) {
            // TODO: log error
            return make_result(nullptr, std::make_shared<Error>(err3->getCode(), "Internal Server Error"));
        }
    }

    return make_result(std::make_shared<LoginResponse>(name, email, sessionID, std::move(subscriptions)));
}

Result<std::shared_ptr<EmptyResponse>> AuthService::Logout(const LogoutRequest& req) {
    // TODO: implement
    return make_result(
        std::make_shared<EmptyResponse>(),
        repo->RemoveSession(req.sessionID));
}

}
