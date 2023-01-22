#ifndef KNNCLIENT_H
#define KNNCLIENT_H
#include <string>
#include <vector>
#include <thread>

using namespace std;

/*
the class create server to the client.
*/
class KnnClient {
private:
    char* m_ip;
    int m_port;
    int m_socket;
public:
    /*
    Constructor.
    ip - the ip.
    port - the port.
    */
    KnnClient(char* ip, int port);

    /*
    Destructor.
    */
    ~KnnClient();

    /*
    this function open socket.
    */
    void openSocket();

    /*
    this function shows the menu to the user and activate the command in the server
    */
    void activateClient();
};

#endif