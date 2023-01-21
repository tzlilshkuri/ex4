#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "DefaultIO.h"

using namespace std;

class Command {
protected:
    string m_description;
    DefaultIO* m_dio;
public:
    virtual void execute() = 0; //may call load for files
};

#endif