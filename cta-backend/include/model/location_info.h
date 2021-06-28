#ifndef __LOCATION_INFO_H__
#define __LOCATION_INFO_H__

#include <string>
#include <serializable.h>

namespace cta {

struct LocationInfo final : public Serializable {
    std::string countryCode;
    // TODO: implement

public:
    // ctor
    LocationInfo() = default;
    LocationInfo(const std::string& countryCOde)
        : countryCode{countryCode} {}

    std::shared_ptr<Error> Deserialize(const Serializer& serializer, void* src) override {
        return serializer.Deserialize(*this, src);
    }
};

}

#endif // __LOCATION_INFO_H__
