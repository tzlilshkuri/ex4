#ifndef KNNCLIENT_H
#define KNNCLIENT_H
#include <string>
using namespace std;
#include <vector>

/*
the class create server to the client.
*/
class KnnClient
{
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
    myVector- the input we want to send the server- vector, distance and K neighbors.
    this function check if the distance and port are valid.
    */
    bool isValidFields(vector<string> myVector);

    /*
    this function open socket.
    */
    void openSocket();

    /*
     this function open the server.
    */
    void activateClient();

    /*
     this function send message to the server.
    */
    void sendMessage(string message);
};

#endif