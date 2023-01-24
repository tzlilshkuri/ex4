#include "Command.h"
#include "SocketIO.h"
#include "MyFileReader.h"
#include "BuildVector.h"
#include "Garden.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Update.h"
#include <iostream>

using namespace std;

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
Update::Update(int client, string* pathTrain, string* pathWrite, int* k, string* mat, vector<string>* mys, bool* files) {
    m_dio = new SocketIO(client);
    m_description = "3";
    m_pathTrain = pathTrain;
    m_pathWrite = pathWrite;
    m_client = client;
    m_k = k;
    m_mat = mat;
    m_mys = mys;
    m_haveFiles = files;
}

/*
the function that activate the command
*/
void Update::execute() {
    if (!*m_haveFiles) {
        m_dio->write("please upload data");
        m_dio->read();
        return;
    }
    Garden mygarden;
    mygarden.load(*m_pathTrain);
    try {
        m_mys->clear();
        m_myFile.open(*m_pathWrite);
        string line;
        while (getline(m_myFile, line)) {
            Flower f(line,',',"defult");
            f.updateType(mygarden.getKSmallest(f, *m_k, *m_mat));
            m_mys->push_back(f.getType());
        }
        m_dio->write("classifying data complete");
        m_dio->read();
        m_myFile.close();
    } catch(invalid_argument& x) {
        throw;
    }
}

/*
destructor
*/
Update::~Update() {
    delete m_dio;
}