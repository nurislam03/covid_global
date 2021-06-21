#ifndef __EMPTY_RESPONSE_H__
#define __EMPTY_RESPONSE_H__

#include <serializable.h>
#include <response/service_response.h>

namespace cta {

struct EmptyResponse final : public ServiceResponse, public Serializable {
    std::string Serialize(Serializer&) const override;
};

}

#endif // __EMPTY_RESPONSE_H__