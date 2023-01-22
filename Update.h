#ifndef UPDATE_H
#define UPDATE_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*
the file update the types of the unclassified file
*/
class Update : public Command{
private:
    string* m_pathTrain;
    string* m_pathWrite;
    int m_client;
    fstream m_myFile;
    int* m_k;
    string* m_mat;
    vector<string>* m_mys; 
    bool *m_haveFiles;
public:
    /*
    client - the client's id for socket
    pathTrain - pointer to the updates path of the classified file
    pathWrite - pointer to the updates path of the unclassified file
    k - the pointer to the updated nearest k
    mat - pointer to the updated matric calculation
    mys - pointer to the updated types of the unclassified file
    files - tell me if i have files or not
    constructor
    */
    Update(int client, string* pathTrain, string* pathWrite , int* k, string* mat, vector<string>* mys, bool *files);
    /*
    the function that activate the command
    */
    void execute();
    /*
    destructor
    */
    ~Update();
};

#endif