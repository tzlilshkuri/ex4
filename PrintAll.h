#ifndef PRINTALL_H
#define PRINTAL_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"
#include <iostream>
#include <fstream>
#include <sstream>


class PrintAll : public Command{
private:
    string* m_pathTrain;
    int m_client;
    fstream m_myFile;
    vector<string>* m_mys; 
public:
    PrintAll(int client, string* pathTrain , vector<string>* mys);
    void execute();
    ~PrintAll();
};








#endif