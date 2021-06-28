#ifndef __CTA_DEF_H__
#define __CTA_DEF_H__

#include <chrono>

namespace cta {

namespace chrono = std::chrono;
using time_point = chrono::time_point<chrono::system_clock>;
using duration = chrono::duration<int>;

}
#endif // __CTA_DEF_H__
