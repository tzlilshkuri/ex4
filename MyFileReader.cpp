#include "MyFileReader.h"
#include "BuildVector.h"
#include <stdexcept>
using namespace std;

/*
Constructor
*/
MyFileReader::MyFileReader() {   
}

/*
path - the csv file we want to open.
we check this things:
first, file is not excel type.
second, file not open succesfully.
third, empty file.
Constructor
*/
void MyFileReader::load(string path) {
    std::string fn = path;
    if (fn.substr(fn.find_last_of(".") + 1) != "csv") {
        throw invalid_argument("Error, type of file does not match!");
    } 
    m_myFile.open(path); 
    if (m_myFile.fail()) {
	    m_myFile.clear();
        throw invalid_argument("Error, no file found!"); 
    }
    if (m_myFile.peek() == std::ifstream::traits_type::eof()) {
        m_myFile.close();
        throw invalid_argument("Error, empty file!");
    }
}

/*
Destructor
*/
MyFileReader::~MyFileReader() {
    m_myFile.close();
}

/*
getGarden - this function takes vector and turns it into a flower by doing the following steps:
separates the vector according to its type and according to its characteristics.
This function also checking the all the vectore are in the same size- if not the user 
wil get an error.
*/
vector<Flower> MyFileReader::getGarden() {
    BuildVector buildV; 
    string line;
    while (getline(m_myFile, line)) {
        int i = (line.length()) -1;
        while (line[i] != ',' && i > 0) {
            i--;
        }
        if (!buildV.makeNewVector(line.substr(0,i), ',').size()) {
            m_myFile.close();
            throw invalid_argument("Invalid File");
        }
        m_myGarden.push_back(Flower(line.substr(0,i), ',' , line.substr(i+1)));
    }
    for (int i = 1; i < m_myGarden.size(); i++) {
        if (m_myGarden[i].getAtrr().size() != m_myGarden[i-1].getAtrr().size() ) {
            m_myFile.close();
            throw invalid_argument("Invalid File");
        }
    }
    return m_myGarden;
}

void MyFileReader::write(string data) {
    m_myFile << data;
}

string MyFileReader::read() {
    string line;
    getline(m_myFile, line);
    return line;
}

bool MyFileReader::sendFile(SocketIO socket) {
    string line;
    while (getline(m_myFile, line)) {
        socket.write(to_string(line.size()) + "-" + line);
        if (socket.read() == "invalid input") {
            return false;
        }
    }
    socket.write("1-");
    cout << socket.read() << endl;
    return true;
}

int validLine(vector<string> vec, int test) {
    BuildVector bv;
    if (vec[0] != "AUC" && vec[0] != "MIN" && vec[0] != "CHB" 
    && vec[0] != "MAN" && vec[0] != "CAN" && !test) {
        return 0;
    }
    return bv.makeNewVector(vec[1 - test], ',').size();
}

bool MyFileReader::create(string path, DefaultIO* socket, int* vecSize, int test) {
    m_myFile.open(path, ios::in | ios::out);
    string line = "";
    BuildVector bv;
    vector<string> vec;
    while (true) {
        line = socket->read();
        if (line == "1-") {
            break;
        }
        if (line == "0-") {
            socket->write("invalid input");
            remove(path.c_str());
            return false;
        }
        line = line.substr(line.find('-') + 1);
        vec = bv.splitEnd(line, ',', 1 - test);
        if (*vecSize == -1) {
            *vecSize = validLine(vec, test);
        }
        if (validLine(vec, test) && *vecSize == validLine(vec, test)) {
            socket->write("1");
        } else {
            socket->write("invalid input");
            remove(path.c_str());
            return false;
        }
    }
    return true;
}