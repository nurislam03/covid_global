#ifndef __BSON_SERIALIZER_H__
#define __BSON_SERIALIZER_H__

#include <serializable.h>

namespace cta {

struct BsonSerializer final : public Serializer {

    std::shared_ptr<Error> Deserialize(LocationInfo&, void *) const override;
    std::shared_ptr<Error> Deserialize(User&, void *) const override;
    std::shared_ptr<Error> Deserialize(SessionInfo&, void *) const override;
    std::shared_ptr<Error> Deserialize(SubscriptionInfo&, void *) const override;

};

}


#endif // __BSON_SERIALIZER_H__