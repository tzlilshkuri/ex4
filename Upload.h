#ifndef UPLOAD_H
#define UPLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"

/*
this class upload the files to the server
*/
class Upload : public Command {
private:
    string* m_pathTrain;
    string* m_pathWrite;
    bool* m_files;
    int m_client;
public:
    /*
    client - the client's id for socket
    pathTrain - pointer to the updates path of the classified file
    pathWrite - pointer to the updates path of the unclassified file
    haveFiles - tell me if i have files or not
    constructor
    */
    Upload(int client, string* pathTrain, string* pathWrite, bool* haveFiles);
    /*
    the function that activate the command
    */
    void execute();
    /*
    destructor
    */
    ~Upload();
};

#endif