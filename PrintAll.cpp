#include "Command.h"
#include "SocketIO.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "PrintAll.h"
#include <iostream>


PrintAll::PrintAll(int client, string* pathTrain, vector<string>* mys) {
    m_dio = new SocketIO(client);
    m_pathTrain = pathTrain;
    m_client = client;
    m_mys=mys;
}

int i=1;
void PrintAll::execute(){
try {
        m_myFile.open("notS.csv");
        string line;
        while (getline(m_myFile, line)) {
        line= to_string(i) +"    " + line;
        m_dio->write(line);
        m_dio->read();
        i++;
        }
        m_dio->write("0-");
        m_dio->read();
        m_myFile.close();
    } catch(invalid_argument& x) {
        throw;
    }



}

PrintAll::~PrintAll() {
    delete m_dio;
}