#include "Command.h"
#include "SocketIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PrintAll.h"
#include <iostream>

/*
client - the client connection id
mys - pointer to the types of the unclsified file
files - tells me i have files to read from
constructor
*/
PrintAll::PrintAll(int client, vector<string>* mys,  bool *files) {
    m_dio = new SocketIO(client);
    m_client = client;
    m_mys = mys;
    m_haveFiles = files;
}

/*
the function that activate the command
*/
void PrintAll::execute(){
    string error = "";
    if (m_mys->size() == 0) {
        error= "please classify the data";
    }
    if (!*m_haveFiles) {
        if (error == ""){
            error = "please upload data";
        } else {
            error = "please upload data\n" + error;
        }
    }
    if (error != "") {
        m_dio->write(error);
        m_dio->read();
        return;
    }
    m_dio->write("0-");
    m_dio->read();
    for (int i = 0; i < m_mys->size(); i++) {
        m_dio->write(to_string(i+1) + "\t" + (*m_mys)[i]);
        m_dio->read();     
    }
    m_dio->write("Done.");
    m_dio->read(); 
}

/*
destructor
*/
PrintAll::~PrintAll() {
    delete m_dio;
}