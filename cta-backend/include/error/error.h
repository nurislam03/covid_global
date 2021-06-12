/**
 * 
 * declars different errors
 * 
 */

#include <string>

namespace cta {

class Error {
    int code;
    std::string msg;

    Error(int code, std::string msg)
    : code{code}, msg{msg} {}

    int getCode() const { return code; }
    std::string getMessage() const { return msg; }
};

}
