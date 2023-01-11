#ifndef KNN_SERVER_H
#define KNN_SERVER_H
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Garden.h"

using namespace std;

/*the class handle the server side of the program*/
class KnnServer {
private:
    int m_socket;
    int m_port;
    int m_clint;
    Garden m_garden;
public:
    /*
    port - the port of the socket
    constructor
    */
    KnnServer(int port);
    /*
    path - a path to file
    the function load the file and create the socker
    */
    void load(string path);
    /*
    buffer - the string i want to send
    the function return the string i want to send
    */
    string createMess(string buffer);
    /*
    the function run without stop(unless connection issues)
    the function run and connect to a client and recive vector matric calculation
    and k nearest in the socket and send the the result of the calculation
    */
    void recAndSend();
    /*
    destructor
    */
    ~KnnServer();
};

#endif