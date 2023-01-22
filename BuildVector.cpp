#include "BuildVector.h"

using namespace std;

/*
constructor
*/
BuildVector::BuildVector() {
}

/*
line - a string i want to split
sep - a note that separate the numbers
the function return vector of doubles the numbers are from the
line and separated by sep
*/
vector<double> BuildVector::makeNewVector(string line, char sep) {
    size_t offset;
    vector<double> ret;
    double val = 0;
    int shows = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == sep) {
            shows++;
        }
    }
    vector<string> vals = splitEnd(line, sep, shows);
    for (int i = vals.size() - 1; i >= 0; i--) {
        try {
            val = stod(vals[i], &offset);
            if(offset != vals[i].length()) {
                ret.clear();
                return ret;
            }
            ret.push_back(val);
        } catch (exception e) {
            ret.clear();
        }
    }
    return ret;
}

/*
str - the string i want to reverse
len - the length of the string
the function return the rvevese string of str
*/
string reverse(string str, int len) {
    char tmp;
    for (int i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
    return str;
}

/*
line - the line i want to separate
sep - the that separate the string
shows - the number of shows i want to separate from the end
the function return vector that contains parts of lines that separated by sep from the 
end by the number of shows
*/
vector<string> BuildVector::splitEnd(string line, char sep, int shows) {
    vector<string> ret;
    string subStr = "";
    int i = line.length() - 1, lastIndex = line.length() - 1;
    if (shows == 0) {
        ret.push_back(line);
        return ret;
    }
    while (shows--) {
        while (i > -1 && line[i] != sep) {
            subStr += line[i--];
        }
        ret.push_back(reverse(subStr, subStr.length()));
        subStr = "";
        if (i > -1 && line[i] == sep && shows) {
            i--;
        }
    }
    if (i == -1) {
        i = 0;
    }
    ret.push_back(line.substr(0, i));
    return ret;
}