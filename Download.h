#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "Flower.h"

using namespace std;

class Download : public Command{
private:
    bool* m_send;
    string* m_path;
public:
    Download(int client, string* path, bool* m_send);
    void execute();
    ~Download();
};

#endif