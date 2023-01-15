#ifndef DEFAULTIO_H
#define DEFAULTIO_H
#include <string>

using namespace std;

class DefaultIO {
private:
public:
    virtual void write(string data) = 0;
    virtual string read() = 0;
};

#endif