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
    bool m_haveFiles;
    bool m_canSend;
    string m_mat;
    string m_pathTrain;
    string m_pathWrite;
    vector<string> mys; 
public:
    CLI(int client, int socket);
    void start();
    ~CLI();
};

#endif