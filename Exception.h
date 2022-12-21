

#ifndef EXEPPTION_H
#define EXEPPTION_H


#include <string>
using namespace std;
class Exception{
private:
    string _error;
public:
    Exception(string error);
    string return_error();
};

#endif 