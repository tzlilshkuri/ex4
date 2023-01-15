#include "StandardIO.h"
#include <iostream>

void StandardIO::write(string data) {
    cout << data << endl;
}

string StandardIO::read() {
    string line;
    getline(cin, line);
    return line;
}