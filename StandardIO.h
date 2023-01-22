#ifndef STANDARDIO_H
#define STANDARDIO_H
#include <string>
#include "DefaultIO.h"

using namespace std;

/*
the class use the keyboard and the screen for communication
*/
class StandardIO : DefaultIO {
private:
public:
    /*
    the function return the string from the kewboard
    */
    string read();
    /*
    data - the data i want to print
    the function print to the screen the data
    */
    void write(string data);
};

#endif