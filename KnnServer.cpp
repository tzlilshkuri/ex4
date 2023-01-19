#include "KnnServer.h"
#include "BuildVector.h"
#include <stdexcept>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "CLI.h"

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
void KnnServer::load() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        throw invalid_argument("Error, in creation socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);
    if (bind(m_socket, (struct sockaddr*)& sin, sizeof(sin)) < 0) {
        throw invalid_argument("error binding socket");
    }
    if (listen(m_socket, 10) < 0) {
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
        int client_socket = accept(m_socket, (struct sockaddr*)& client_sin, &addr_len);
        if (client_socket < 0) {
            throw invalid_argument("error accepting client");
        }
        thread t([this, client_socket]() {
            CLI cli(client_socket, m_socket);
            cli.start();
        });
        t.detach();
        m_thread_pool.push_back(move(t));
    }
}

/*
destructor
*/
KnnServer::~KnnServer() {
    for (auto& t : m_thread_pool) {
        if (t.joinable()) {
            t.join();
        }
    }
    close(m_socket);
}