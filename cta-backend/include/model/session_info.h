#ifndef __SESSION_INFO_H__
#define __SESSION_INFO_H__

#include <string>
#include <serializable.h>
#include <chrono>
#include <def.h>

namespace cta {

struct SessionInfo final : public Serializable {
    std::string sessionID;
    std::string email;
    time_point create_time;

public:
    // ctor
    SessionInfo() = default;
    SessionInfo(const std::string& id, const std::string& email, const time_point& create_time)
        : sessionID{id}, email{email}, create_time{create_time} {}

    std::shared_ptr<Error> Deserialize(const Serializer& serializer, void* src) override {
        return serializer.Deserialize(*this, src);
    }

};

}

#endif // __SESSION_INFO_H__

