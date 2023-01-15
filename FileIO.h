#ifndef FILEIO_H
#define FILEIO_H
#include <stdexcept>
#include "DefaultIO.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class FileIO : DefaultIO {
private:
    fstream m_myFile;
public:
    FileIO(string path);
    void write(string data);
    string read();
    ~FileIO();
};

#endif