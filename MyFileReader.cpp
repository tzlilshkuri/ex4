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