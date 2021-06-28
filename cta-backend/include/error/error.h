/**
 * 
 * declars different errors
 * 
 */

#ifndef __CTA_ERROR_H__
#define __CTA_ERROR_H__

#include <string>

namespace cta {

class Error {
public:
    enum class CODE {
        ERR_NONE,
        ERR_PASS,
        ERR_VALIDATION,
        ERR_WRONG_PASSWORD,
        ERR_NOTFOUND,
        ERR_UNAUTHORIZED,
        ERR_REPO,
        ERR_DUPLICATE_USER,
        ERR_BLOCKED,
        ERR_PARSE,
        ERR_UNKNOWN
    };

    Error(CODE code, std::string msg)
    : code{code}, msg{msg} {}

    CODE getCode() const { return code; }
    std::string getMessage() const { return msg; }

private:
    CODE code;
    std::string msg;
};

}

#endif //__CTA_ERROR_H__