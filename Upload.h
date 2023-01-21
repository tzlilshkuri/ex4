#ifndef UPLOAD_H
#define UPLOAD_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"

class Upload : public Command{
private:
    string* m_pathTrain;
    string* m_pathWrite;
    bool* m_files;
    int m_client;
public:
    Upload(int client, string* pathTrain, string* pathWrite, bool* haveFiles);
    void execute();
    ~Upload();
};

#endif