#ifndef __EMAIL_NOTIFIER_H__
#define __EMAIL_NOTIFIER_H__

#include <notifier.h>

namespace cta {

class EmailNotifier final : public Notifier {

public:
    std::shared_ptr<Error> SendNotification(const std::list<std::string> email, const std::string& subject, const std::string& msg) override;
};

}

#endif // __EMAIL_NOTIFIER_H__