#ifndef __HTTPNOTIFIER_H__
#define __HTTPNOTIFIER_H__

#include <notifier.h>

namespace cta {

class HTTPNotifier final : public Notifier {
    std::string notifyEndpoint;

public:
    HTTPNotifier(const std::string& notifyEndpoint);

    std::shared_ptr<Error> SendNotification(const std::list<std::string>& recipients, const std::string& subject, const std::string& msg) override;
};

}

#endif // __HTTPNOTIFIER_H__