#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__

#include <string>

namespace cta {

    // Forward declaration
class GetAllLocationInfoResponse;
class EmptyResponse;
class LoginResponse;
class SearchResponse;

struct Serializer {
    virtual std::string Serialize(const GetAllLocationInfoResponse&) const = 0;
    virtual std::string Serialize(const EmptyResponse&) const = 0;
    virtual std::string Serialize(const LoginResponse&) const = 0;
    virtual std::string Serialize(const SearchResponse&) const = 0;
};


struct Serializable {
    virtual std::string Serialize(const Serializer&) const = 0;
};

}

#endif // __SERIALIZABLE_H__