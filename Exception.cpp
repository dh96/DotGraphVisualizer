

#include "Exception.h"

Exception::Exception(string error) {
    _error=error;
}

string Exception::return_error() {
    return _error;
}

