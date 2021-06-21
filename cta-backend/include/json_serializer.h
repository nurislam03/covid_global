#ifndef __JSON_SERIALIZER_H__
#define __JSON_SERIALIZER_H__

#include <serializable.h>

namespace cta {

struct JsonSerializer final : public Serializer {
    std::string Serialize(const GetAllLocationInfoResponse&) const override;
    std::string Serialize(const EmptyResponse&) const override;
    std::string Serialize(const LoginResponse&) const override;
    std::string Serialize(const SearchResponse&) const override;
};

}

#endif // __JSON_SERIALIZER_H__