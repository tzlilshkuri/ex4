#ifndef BUILD_VECTOR_H
#define BUILD_VECTOR_H
#include <vector>
#include <string>

using namespace std;

/*
the class create vectors 
*/
class BuildVector {
private:
public:
    /*
    constructor
    */
    BuildVector();
    /*
    line - a string i want to split
    sep - a note that separate the numbers
    the function return vector of doubles the numbers are from the
    line and separated by sep
    */
    vector<double> makeNewVector(string line, char sep);

    /*
    line - the line i want to separate
    sep - the that separate the string
    shows - the number of shows i want to separate from the end
    the function return vector that contains parts of lines that separated by sep from the 
    end by the number of shows
    */
    vector<string> splitEnd(string line, char sep, int shows);
};

#endif