#ifndef PRINTALL_H
#define PRINTAL_H
#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*
this class send the types of the unclsified file to the client and print it
*/
class PrintAll : public Command{
private:
    int m_client;
    fstream m_myFile;
    vector<string>* m_mys; 
    bool *m_haveFiles;
public:
    /*
    client - the client connection id
    mys - pointer to the types of the unclsified file
    files - tells me i have files to read from
    constructor
    */
    PrintAll(int client, vector<string>* mys, bool *files);
    /*
    the function that activate the command
    */
    void execute();
    /*
    destructor
    */
    ~PrintAll();
};

#endif