#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__

#include <string>
#include <error/error.h>
#include <memory>

namespace cta {

    // Forward declaration
class GetAllLocationInfoResponse;
class EmptyResponse;
class LoginResponse;
class SearchResponse;
class LocationInfo;
class User;
class SessionInfo;
class SubscriptionInfo;

struct Serializer {
    virtual std::string Serialize(const GetAllLocationInfoResponse&) const;
    virtual std::string Serialize(const EmptyResponse&) const;
    virtual std::string Serialize(const LoginResponse&) const;
    virtual std::string Serialize(const SearchResponse&) const;

    virtual std::shared_ptr<Error> Deserialize(LocationInfo&,  void*) const;
    virtual std::shared_ptr<Error> Deserialize(User&, void*) const;
    virtual std::shared_ptr<Error> Deserialize(SessionInfo&, void*) const;
    virtual std::shared_ptr<Error> Deserialize(SubscriptionInfo&, void*) const;
};


struct Serializable {
    virtual std::string Serialize(const Serializer&) const;
    virtual std::shared_ptr<Error> Deserialize(const Serializer&, void*);
};

}

#endif // __SERIALIZABLE_H__