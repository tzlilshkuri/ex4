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

Update::Update(int client, string* pathTrain, string* pathWrite , int* k, string* mat, vector<string>* mys) {
    m_dio = new SocketIO(client);
    m_description = "3";
    m_pathTrain = pathTrain;
    m_pathWrite = pathWrite;
    m_client = client;
    m_k = k;
    m_mat = mat;
    m_mys=mys;
}


// MyFileReader toRead; 
// toRead.load("yesS.csv");
// vector<Flower> myOldGarden= toRead.getGarden();

void Update::execute(){
Garden mygarden;
mygarden.load("yesS.csv");
int j=1;
 try {
        m_myFile.open("notS.csv");
        string line;
        while (getline(m_myFile, line)) {
        Flower f(line,',',"defult");
        f.updateType(mygarden.getKSmallest(f, *m_k, *m_mat));
        m_mys->push_back(f.getType());
        }
        m_myFile.close();
    } catch(invalid_argument& x) {
        throw;
    }
m_myFile.open("notS.csv", std::ios::out | std::ios::trunc);
for (int i = 0; i < m_mys->size(); i++)
    {
        m_myFile << (*m_mys)[i] << endl;
    }
    m_myFile.close();
}


Update::~Update() {
    delete m_dio;
}

