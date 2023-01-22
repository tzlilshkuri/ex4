#ifndef SETTINGS_H
#define SETTINGS_H
#include "Command.h"
#include "SocketIO.h"

/*
the command update the k nearest and the matric calculation
*/
class Settings : public Command {
private:
    int* m_k;
    string* m_mat;
public:
    /*
    client - client's id of the socket
    m_k - pointer to the updated k nearest
    m_mat - pointer to the updated matric calculation
    constructor
    */
    Settings(int client, int* m_k, string* m_mat);
    /*
    the function that activate the command
    */
    void execute();
    /*
    destructor
    */
    ~Settings();
};

#endif