#include "SocketIO.h"

#define BUFFER_SIZE 4096

/*
client - the client's id for socket
*/
SocketIO::SocketIO(int client) {
    m_client = client;
}

/*
the function recive data to her destination with socket
*/
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

/*
data - string i want to send
the function send data to her destination with socket
*/
void SocketIO::write(string data) {
    int sent_bytes = send(m_client, data.c_str(), data.length(), 0);
    if (sent_bytes < 0) {
        throw invalid_argument("error sending to client");
    }
}