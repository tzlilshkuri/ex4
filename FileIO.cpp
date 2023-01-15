#include "FileIO.h"

FileIO::FileIO(string path) {
    if (path.substr(path.find_last_of(".") + 1) != "csv") {
        throw invalid_argument("Error, type of file does not match!");
    }
    m_myFile.open(path, ios::in | ios::out); 
    if (m_myFile.fail()) {
	    m_myFile.clear();
        throw invalid_argument("Error, no file found!"); 
    }
    if (m_myFile.peek() == std::ifstream::traits_type::eof()) {
        m_myFile.close();
        throw invalid_argument("Error, empty file!");
    }
}

void FileIO::write(string data) {
    m_myFile << data;
}

string FileIO::read() {
    string line;
    getline(m_myFile, line);
    return line;
}

FileIO::~FileIO() {
    m_myFile.close();
}