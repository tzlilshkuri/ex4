#include "KnnServer.h"
#include "BuildVector.h"
#include <stdexcept>

using namespace std;

#define BUFFER_SIZE 4096

/*
port - the port of the socket
constructor
*/
KnnServer::KnnServer(int port) {
    m_port = port;
}

/*
buffer - the string i want to send
the function return buffer after manipulation 
*/
string KnnServer::createMess(string buffer) {
    BuildVector buildV;
    vector<string> rec = buildV.splitEnd(buffer, ' ', 2);
    if (buildV.makeNewVector(rec[2], ' ').size() != m_garden.getSizeAtt()) {
        return "invalid input";
    }
    Flower clientFlower(rec[2], ' ', "");
    clientFlower.updateType(m_garden.getKSmallest(clientFlower, stoi(rec[0]), rec[1]));
    return clientFlower.getType();
}

/*
path - a path to file
the function load the file and create the socker
*/
void KnnServer::load(string path) {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        throw invalid_argument("Error, in creation socket");
    }
    try {
        m_garden.load(path);
    } catch(invalid_argument& x) {
        throw;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);
    if (bind(m_socket, (struct sockaddr*)& sin, sizeof(sin)) < 0) {
        throw invalid_argument("error binding socket");
    }
    if (listen(m_socket, 5) < 0) {
        throw invalid_argument("error listening to a socket");
    }
}

/*
the function run without stop(unless connection issues)
the function run and connect to a client and recive vector matric calculation
and k nearest in the socket and send the the result of the calculation
*/
void KnnServer::recAndSend() {
    while (true) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        m_clint = accept(m_socket, (struct sockaddr*)& client_sin, &addr_len);
        string snd = "";
        if (m_clint < 0) {
            throw invalid_argument("error accepting client");
        }
        while (true) {
            char buffer[BUFFER_SIZE];
            memset(buffer, 0, BUFFER_SIZE);
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(m_clint, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                break;
            } else if (read_bytes < 0) {
                throw invalid_argument("error");
            } else {
                if (strcmp(buffer, "-1") == 0) {
                    break;
                }
                snd = createMess(buffer);
            }
            int sent_bytes = send(m_clint, snd.c_str(), snd.length(), 0);
            if (sent_bytes < 0) {
                throw invalid_argument("error sending to client");
            }
        }
    }
}

/*
destructor
*/
KnnServer::~KnnServer() {
    close(m_socket);
}