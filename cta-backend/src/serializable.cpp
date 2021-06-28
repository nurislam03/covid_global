#include <serializable.h>
#include <memory>
#include <error/exception.h>

namespace cta {


// Serializer
std::string Serializer::Serialize(const GetAllLocationInfoResponse&) const {
    throw not_implemented{};
}

std::string Serializer::Serialize(const EmptyResponse&) const {
    throw not_implemented{};
}

std::string Serializer::Serialize(const LoginResponse&) const {
    throw not_implemented{};
}

std::string Serializer::Serialize(const SearchResponse&) const {
    throw not_implemented{};
}

std::shared_ptr<Error> Serializer::Deserialize(LocationInfo&, void*) const {
    throw not_implemented{};
}
std::shared_ptr<Error> Serializer::Deserialize(User&, void*) const {
    throw not_implemented{};
}
std::shared_ptr<Error> Serializer::Deserialize(SessionInfo&, void*) const {
    throw not_implemented{};
}
std::shared_ptr<Error> Serializer::Deserialize(SubscriptionInfo&, void*) const {
    throw not_implemented{};
}



// Serializable
std::string Serializable::Serialize(const Serializer&) const {
    throw not_implemented{};
}

std::shared_ptr<Error> Serializable::Deserialize(const Serializer&, void*) {
    throw not_implemented{};
}

}