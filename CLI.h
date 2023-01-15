#ifndef CLI_H
#define CLI_H
#include "Command.h"
#include <vector>

using namespace std;

class CLI {
private:
    vector<Command> m_command;
public:
    CLI();
    /*
    command - the index of the command
    info - the additional information that the command need to start
    */
    void start();
};

#endif