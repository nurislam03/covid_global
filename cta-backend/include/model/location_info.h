#ifndef __LOCATION_INFO_H__
#define __LOCATION_INFO_H__

#include <string>
#include <chrono>
#include <serializable.h>

namespace cta {

using time_point = std::chrono::time_point<std::chrono::system_clock>;

struct LocationInfo final : public Serializable {
    std::string countryCode;
    std::string countryName;
    std::string stateName;
    std::string citizenNntry;
    std::string foreignersEntry;
    std::string tourismStatus;
    std::string quarantineStatus;
    std::string lockdownStatus;
    std::string breakingNews;
    std::string airlinesUpdate;
    std::string entryPolicyForeigners;
    std::string entryPolicyCitizen;
    std::string quarantinePolicyForeigners;
    std::string quarantinePolicyCitizen;
    std::string certificationForeigners;
    std::string certificationCitizen;
    std::string travelRegulationRestriction;
    std::string flightRegulationRestriction;
    int totalCase;
    int newCase;
    int activeCase;
    int criticalCase;
    int totalDeaths;
    int newDeath;
    std::string zoneStatus;
    time_point createdDate;
    time_point updatedDate;

public:
    // ctor
    LocationInfo() = default;

    std::shared_ptr<Error> Deserialize(const Serializer& serializer, void* src) override {
        return serializer.Deserialize(*this, src);
    }
};

}

#endif // __LOCATION_INFO_H__
