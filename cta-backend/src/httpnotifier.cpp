#include <httpnotifier.h>
#include <cpp-httplib/httplib.h>
#include <json/json.hpp>

namespace cta {

HTTPNotifier::HTTPNotifier(const std::string& notifyEndpoint)
    : notifyEndpoint{notifyEndpoint} {}

std::shared_ptr<Error> HTTPNotifier::SendNotification(const std::list<std::string>& recipients, const std::string& subject, const std::string& msg) {

    httplib::Client cli(notifyEndpoint.c_str());

    // TODO: move this to json serializer
    nlohmann::json payload = {
        {"subject", subject},
        {"message", msg},
        {"recipents", recipients}
    };

    auto res = cli.Post("/email/send/", payload.dump(), "application/json");
    if (res->status != 200) {
        return std::make_shared<Error>(Error::CODE::ERR_NOTIFY, "Failed to send notification");
    }

    return nullptr;
}

}