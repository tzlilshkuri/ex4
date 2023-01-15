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

class SocketIO : DefaultIO {
private:
    int m_socket;
    int m_port;
    int m_client;
public:
    SocketIO(int socket, int port, int client);
    void write(string data);
    string read();
};

#endif