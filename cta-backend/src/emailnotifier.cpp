#include <email_notifier.h>
#include <iostream>

namespace cta {

std::shared_ptr<Error> 
EmailNotifier::SendNotification(
    const std::string& email, const std::string& subject, const std::string& msg
) {

    std::cout << "EmailNotifier::SendNotification is called\n";

    return nullptr;

}

}