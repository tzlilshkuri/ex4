#ifndef STANDARDIO_H
#define STANDARDIO_H
#include <string>
#include "DefaultIO.h"

using namespace std;

class StandardIO : DefaultIO {
private:
public:
    string read();
    void write(string data);
};

#endif