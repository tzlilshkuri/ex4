#ifndef CLI_H
#define CLI_H
#include "Command.h"
#include <vector>

using namespace std;

class CLI {
private:
    vector<Command*> m_command;
    int m_socket;
    int m_k;
    int m_client;
    string m_mat;
    string m_pathTrain;
    string m_pathWrite;
public:
    CLI(int client, int socket);
    /*
    command - the index of the command
    info - the additional information that the command need to start
    */
    void start();
    ~CLI();
};

#endif