#ifndef UPDATE_H
#define UPDATE_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"
#include <iostream>
#include <fstream>
#include <sstream>


class Update : public Command{
private:
    string* m_pathTrain;
    string* m_pathWrite;
    int m_client;
    fstream m_myFile;
    int* m_k;
    string* m_mat;
    vector<string>* m_mys; 
public:
    Update(int client, string* pathTrain, string* pathWrite , int* k, string* mat, vector<string>* mys);
    void execute();
    ~Update();
};

#endif