#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "Flower.h"

using namespace std;

/*
the commnd that download the file to our computer
*/
class Download : public Command {
private:
    vector<string>* m_mys;
    bool* m_haveFiles;
public:
    /*
    client - client's id socket
    mys - pointer to the types of the flowers
    haveFiles - pointer that tell me if i upload files
    constructor
    */
    Download(int client, vector<string>* mys, bool* haveFiles);
    /*
    the function that activate the command
    */
    void execute();
    /*
    destructor
    */
    ~Download();
};

#endif