#ifndef __USER_H__
#define __USER_H__

#include <serializable.h>

namespace cta {

struct User final : public Serializable  {
    std::string name;
    std::string email;
    std::string pwHash;
    int failedLoginAttemptCount;

public:
    // ctor
    User() = default;
    User(const std::string& name, const std::string& email, const std::string pwHash, int failedLoginAttemptCount)
        : name{name}, email{email}, pwHash{pwHash}, failedLoginAttemptCount{failedLoginAttemptCount} {}

    std::shared_ptr<Error> Deserialize(const Serializer& serializer, void* src) override {
        return serializer.Deserialize(*this, src);
    }
};

}

#endif // __USER_H__