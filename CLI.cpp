#include "CLI.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Settings.h"
#include "Upload.h"
#include "Update.h"
#include "PrintAll.h"
#include "Download.h"

#define BUFFER_SIZE 4096
/*
client - the client's id socket
socket - the server's id socket
constructor
*/
CLI::CLI(int client, int socket) {
    m_mat = "AUC";
    m_k = 5;
    m_client = client;
    m_socket = socket;
    m_haveFiles = false;
    m_command.push_back(new Settings(client, &m_k, &m_mat));
    m_command.push_back(new Upload(client, &m_pathTrain, &m_pathWrite, &m_haveFiles));
    m_command.push_back(new Settings(client, &m_k, &m_mat));
    m_command.push_back(new Update(client, &m_pathTrain, &m_pathWrite,&m_k, &m_mat, &m_mys, &m_haveFiles));
    m_command.push_back(new PrintAll(client, &m_mys, &m_haveFiles));
    m_command.push_back(new Download(client, &m_mys, &m_haveFiles));
}

/*
choose - the choose of the client
the function return true if the client choose valid option else return false
*/
bool validChos(string choose) {
    return choose == "1" || choose == "2" || choose == "3" || choose == "4" || choose == "5" 
    || choose == "8";
}

/*
the function activate the cli
*/
void CLI::start() {
    string menu = "Welcome to the KNN Calssifier Server. Please choose an option:\n" 
                    "1. upload an unclassified csv data file\n2. algorithm settings\n"
                    "3. classify data\n4. display results\n5. download results\n8. exit";
    SocketIO sock(m_client);
    while (true) {
        sock.write(menu);
        string rec = sock.read();
        int fnd = rec.find('-') + 1;
        rec = rec.substr(fnd, rec.size() - fnd);
        if (!validChos(rec)) {
            sock.write("invalid input");
            sock.read();
            continue;
        }
        sock.write(rec);
        sock.read();
        if (rec == "8") {
            return;
        }
        m_command[stoi(rec)]->execute();
    }
}

/*
destructor
*/
CLI::~CLI() {
    for (int i = m_command.size() - 1; i >= 0; i--) {
        delete m_command[i];
    }
    close(m_client);
}