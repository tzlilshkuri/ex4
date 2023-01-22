#ifndef CLI_H
#define CLI_H
#include "Command.h"
#include <vector>

using namespace std;

/*
this class is talked directly to a client and every client has a
cli that he talked with him
*/
class CLI {
private:
    vector<Command*> m_command;
    int m_socket;
    int m_k;
    int m_client;
    bool m_haveFiles;
    string m_mat;
    string m_pathTrain;
    string m_pathWrite;
    vector<string> m_mys; 
public:
    /*
    client - the client's id socket
    socket - the server's id socket
    constructor
    */
    CLI(int client, int socket);
    /*
    the function activate the cli
    */
    void start();
    /*
    distructor
    */
    ~CLI();
};

#endif