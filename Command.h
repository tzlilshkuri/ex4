#ifndef STANDARDIO_H
#define STANDARDIO_H
#include <string>
#include "DefaultIO.h"

using namespace std;

class Command {
private:
    string description;
    DefaultIO* dio;
public:
    virtual void execute() = 0; //may call load for files
};

#endif