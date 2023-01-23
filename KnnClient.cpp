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
sock - socket communication to the server
the function send files to the server
*/
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

/*
sock - socket communication to the server
the function deliver the k neares and the matric to the server
*/
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

/*
sock - socket communication to the server
the function clasiffied the unclassified file in the server
*/
void option3(SocketIO sock) {
    string line = sock.read();
    if (line != "0-"){
        cout << line <<endl;
    }
    sock.write("0-");
}

/*
sock - socket communication to the server
the function get the classified values of the unclassified file and print it
*/
void option4(SocketIO sock) {
    string s = sock.read();
    if (s != "0-"){
        cout << s << endl;
        sock.write("0-");
        return;
    }
    sock.write("0-");
    string line = "";
    while (true) {
        line = sock.read();
        sock.write("0-");
        if (line == "Done.") {
            cout << line <<endl;
            getline(cin, line);
            break;
        }
        cout << line <<endl;
    }
}

/*
sock - socket connection to the server
the function return all the types in the server
*/
vector<string> getTypes(SocketIO sock) {
    vector<string> ret;
    string line;
    while (true) {
        line = sock.read();
        if (line == "0-") {
            sock.write("0-");
            break;
        }
        ret.push_back(line.substr(line.find('-') + 1));
        sock.write("0-");
    }
    return ret;
}

/*
types - the vector of the types in the server
path - the path to file
the function writes to file
*/
void writeToFile(vector<string> types, string path) {
    fstream file;
    file.open(path, ios::out);
    for (int i = 0; i < types.size(); i++) {
        if (!i) {
            file << types[i];
        } else {
            file << "\n" + types[i];
        }
    }
    file.close();
}

/*
sock - socket communication to the server
the function get the classified values of the unclassified file andsave it in a file
*/
void option5(SocketIO sock) {
    string line = sock.read();
    if (line != "0-") {
        cout << line << endl;
        sock.write("0-");
        return;
    }
    getline(cin, line);
    if (line.substr(line.find_last_of(".") + 1) != "csv") {
        sock.write("1-");
        cout << "invalid input" << endl;
        return;
    }
    sock.write("0-");
    vector<string> types = getTypes(sock);
    thread t(writeToFile, types, line);
    t.detach();
}

/*
this function shows the menu to the user and activate the command in the server
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
                option3(sock);
                break;
            }
            case 4: {
                option4(sock);
                break;
            }
            case 5: {
                option5(sock);
                break;
            }
            default: {
                return;
                break;
            }
        }
    }
}