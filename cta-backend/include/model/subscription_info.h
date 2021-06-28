#ifndef __SUBSCRIPTION_INFO_H__
#define __SUBSCRIPTION_INFO_H__

#include <string>
#include <serializable.h>

namespace cta {

struct  SubscriptionInfo final : public Serializable {
    std::string email;
    std::string location;

public:
    // ctor
    SubscriptionInfo() = default;
    SubscriptionInfo(const std::string& email, const std::string& location)
        : email{email}, location{location} {}

    std::shared_ptr<Error> Deserialize(const Serializer& serializer, void* src) override {
        return serializer.Deserialize(*this, src);
    }
};


}

#endif //__SUBSCRIPTION_INFO_H__