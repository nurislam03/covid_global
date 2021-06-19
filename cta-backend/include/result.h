#ifndef __RESULT_H__
#define __RESULT_H__

#include <memory>
#include <error/error.h>

namespace cta {

template <typename T>
using Result = std::pair<T, std::shared_ptr<Error>>;

template <typename T>
Result<T> make_result(T t, const std::shared_ptr<Error>& err = nullptr) {
    return std::make_pair(t, err);
}

}

#endif // __RESULT_H__