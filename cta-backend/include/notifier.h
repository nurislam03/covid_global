#ifndef __NOTIFIER_H__
#define __NOTIFIER_H__

#include <memory>
#include <list>
#include <error/error.h>

namespace cta {

class Notifier {

public:
    virtual std::shared_ptr<Error> SendNotification(const std::list<std::string> email, const std::string& subject, const std::string& msg) = 0;
};

}

#endif // __NOTIFIER_H__