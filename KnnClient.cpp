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
#include "SocketIO.h"
#include "MyFileReader.h"
#include <thread>
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

void option1(SocketIO sock) {
    string line;
    BuildVector bv;
    vector<string> path;
    for (int i = 0; i < 2; i++) {
        cout << sock.read() << endl;
        getline(cin, line);
        MyFileReader file1;
        try {
            file1.load(line);
        } catch (invalid_argument& x) {
            cout << "invalid input" << endl;
            sock.write("1-");
            return;
        }
        //file1.printAll();
        path = bv.splitEnd(line, '/', 1);
        sock.write(to_string(path[0].size()) + "-" + path[0]);
        line = sock.read();
        if (line == "1-") {
            cout << "error" << endl;
            return;
        }
        if (line == "invalid input") {
            cout << line << endl;
            sock.write("0-");
            return;
        }
        if (!file1.sendFile(sock)) {
            return;
        }
    }
}

void option2(SocketIO sock) {
    string line;
    cout << sock.read() << endl;
    getline(cin, line);
    sock.write(to_string(line.size()) + "-" + line);
    line = sock.read();
    if (line != "0-") {
        cout << line << endl;
    }
    sock.write("0-");
}


void option4(SocketIO sock) {
    string line="";
    while (true) {
        line = sock.read();
        sock.write("0-");
        if (line == "0-")
        {
            break;
        }
        cout << line <<endl;

void option5(SocketIO sock) {
    bool start = true;
    string line;
    getline(cin, line);
    if (line.substr(line.find_last_of(".") + 1) != "csv") {
        sock.write("1-");
        cout << "invalid input" << endl;
        return;
    }
    fstream file;
    file.open(line, ios::out);
    if (file.fail()) {
	    file.clear();
        sock.write("1-");
        throw invalid_argument("Error, no file found!"); 
    }
    sock.write("0-");
    while (true) {
        line = sock.read();
        if (line == "0-") {
            sock.write("0-");
            break;
        }
        line = line.substr(line.find('-') + 1);
        if (start) {
            start = false;
            file << line;
        } else {
            file << "\n" + line;
        }
        sock.write("0-");
        file.close();
    }
}

/*
this function open the server.
*/
void KnnClient::activateClient() {
    string line;
    BuildVector buildV;
    SocketIO sock(m_socket);
    while (true) {
        cout << sock.read() << endl;
        getline(cin, line);
        sock.write(to_string(line.size()) + "-" + line);
        line = sock.read();
        sock.write("0-");
        if (line == "invalid input") {
            cout << line << endl;
            continue;
        }
        switch (stoi(line)) {
            case 1: {
                option1(sock);
                break;
            }
            case 2: {
                option2(sock);
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                option4(sock);
                break;
            }
            case 5:
                /*thread t(option5, sock);
                t.join();
                break;*/
                option5(sock);
            default: {
                return;
                break;
            }
        }
    }
}