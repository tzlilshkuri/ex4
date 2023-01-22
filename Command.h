#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "DefaultIO.h"

using namespace std;

/*
abstruct class that represent the commands
*/
class Command {
protected:
    string m_description;
    DefaultIO* m_dio;
public:
    /*
    the function that activate the command
    */
    virtual void execute() = 0;
};

#endif