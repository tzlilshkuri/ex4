#include <iostream>
#include <string>
#include <stdlib.h>
#include "Garden.h"
#include "BuildVector.h"
#include "MyFileReader.h"
#include <string.h>
#include "KnnClient.h"
#include "KnnServer.h"

/*
the first function that run in my program
argv - the arguments that the user enter
argc - the number of arguments
*/
int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "invalid number of args" << endl;
        return 0;
    }
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            cout << "invalid port" << endl;
            return 0;
        }  
    }
    if (!stoi(argv[1])) {
        cout << "invalid port" << endl;
        return 0;
    }
    try {
        KnnServer knnServer(atoi(argv[1]));
        knnServer.load();
        knnServer.recAndSend();
        }
    catch(invalid_argument& e) {
        cout << e.what() << endl;
    }
    return 0;
}