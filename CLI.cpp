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


#define BUFFER_SIZE 4096

CLI::CLI(int client, int socket) {
    m_mat = "AUC";
    m_k = 5;
    m_client = client;
    m_socket = socket;
    m_command.push_back(new Settings(client, &m_k, &m_mat));
    m_command.push_back(new Upload(client, &m_pathTrain, &m_pathTrain));
    m_command.push_back(new Settings(client, &m_k, &m_mat));
}

bool validChos(string choose) {
    return choose == "1" || choose == "2" || choose == "3" || choose == "4" || choose == "5" 
    || choose == "8";
}

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
        m_command[stoi(rec)]->execute();
    }
}

CLI::~CLI() {
    for (int i = m_command.size(); i >= 0; i++) {
        delete m_command[i];
    }
    close(m_socket);
}