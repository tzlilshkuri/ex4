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

class SocketIO : public DefaultIO {
private:
    int m_client;
public:
    SocketIO(int client);
    void write(string data);
    string read();
};

#endif