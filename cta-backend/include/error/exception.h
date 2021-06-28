#ifndef __CTA_EXCEPTION_H__
#define __CTA_EXCEPTION_H__

#include <stdexcept>

namespace cta {

struct not_implemented : public std::logic_error{
    not_implemented() : logic_error("function not implemented") {}
};

}


#endif // __CTA_EXCEPTION_H__