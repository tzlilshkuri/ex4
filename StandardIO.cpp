#include "StandardIO.h"
#include <iostream>

/*
data - the data i want to print
the function print to the screen the data
*/
void StandardIO::write(string data) {
    cout << data << endl;
}

/*
the function return the string from the kewboard
*/
string StandardIO::read() {
    string line;
    getline(cin, line);
    return line;
}