#include "KnnClient.h"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "BuildVector.h"
#include <vector>
#include <stdexcept>
using namespace std;

#define BUFFER_SIZE 4096

/*
Constructor.
ip - the ip.
port - the port.
*/
KnnClient::KnnClient(char* ip, int port) {
    m_ip = ip;
    m_port = port;
}

/*
Destructor.
*/
KnnClient::~KnnClient() {
    close(m_socket);
}

/*
this function open socket.
*/
void KnnClient::openSocket() {
    const char* ip_address = m_ip; 
    const int port_no = m_port;
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        throw invalid_argument ("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_ip);
    sin.sin_port = htons(m_port);
    if (connect(m_socket, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        throw invalid_argument ("error in conection to socket");
    }   
}

/*
myVector- the input we want to send the server- vector, distance and K neighbors.
this function check if the distance and port are valid.
*/
bool KnnClient::isValidFields(vector<string> myVector) {
    if (myVector[1] != "MAN" && myVector[1] != "MIN" && myVector[1] != "AUC" &&
        myVector[1] != "CAN" && myVector[1] != "CHB") {
        return false;
    }
    for (int i = 0; i < myVector[0].size(); i++) {
        if (myVector[0][i] < '0' || myVector[0][i] > '9') {
            return false;
            }  
    }
    if (myVector[0] == "" || !stoi(myVector[0])) {
        return false;
    } 
    return true;
}

/*
this function send message to the server.
*/
void KnnClient::sendMessage(string message) {
    int data_len = message.length();
    int sent_bytes = send(m_socket, message.c_str(), data_len, 0);
    if (sent_bytes < 0) {
        throw invalid_argument("error");
    } 
}

/*
this function open the server.
*/
void KnnClient::activateClient() {
    bool myBool= true;
    string line;
    BuildVector buildV;
    while (myBool) {   
        getline(cin, line);
        vector<string> myVector = buildV. splitEnd(line, ' ', 2); 
        if (line == "-1") {
            sendMessage("-1");
            break;              
        }
        if (!isValidFields(myVector)) {
            cout << "invalid input" << endl;
            continue;
        }
        sendMessage(line);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(m_socket, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            throw invalid_argument("there is no message");
        }
        else if (read_bytes < 0) {
            throw invalid_argument("error");
            }
        else {
            cout << buffer << endl;
        }
    }
}