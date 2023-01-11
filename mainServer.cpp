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
    if (argc != 3 ) {
        cout << "invalid number of args" << endl;
        return 0;
    }
    for (int i = 0; i < strlen(argv[2]); i++) {
        if (argv[2][i] < '0' || argv[2][i] > '9') {
            cout << "invalid port" << endl;
            return 0;
        }  
    }
    if (!stoi(argv[2])) {
        cout << "invalid port" << endl;
        return 0;
    }
    try {
        KnnServer knnServer(atoi(argv[2]));
        knnServer.load(argv[1]);
        knnServer.recAndSend();
        }
    catch(invalid_argument& e) {
        cout << e.what() << endl;
    }
    return 0;
}