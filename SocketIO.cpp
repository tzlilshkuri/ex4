#include "SocketIO.h"

#define BUFFER_SIZE 4096

SocketIO::SocketIO(int client) {
    m_client = client;
}

string SocketIO::read() {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_client, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        return "";
    } else if (read_bytes < 0) {
        throw invalid_argument("error");
    } else {
        return buffer;
    }
}

void SocketIO::write(string data) {
    int sent_bytes = send(m_client, data.c_str(), data.length(), 0);
    if (sent_bytes < 0) {
        throw invalid_argument("error sending to client");
    }
}