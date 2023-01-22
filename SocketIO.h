#ifndef SOCKETIO_H
#define SOCKETIO_H
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include "DefaultIO.h"

using namespace std;

/*
the communication way with socket
*/
class SocketIO : public DefaultIO {
private:
    int m_client;
public:
    /*
    client - the client's id for socket
    */
    SocketIO(int client);
    /*
    data - string i want to send
    the function send data to her destination with socket
    */
    void write(string data);
    /*
    the function recive data to her destination with socket
    */
    string read();
};

#endif