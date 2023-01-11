#ifndef MY_FILE_READER_H
#define MY_FILE_READER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Flower.h"
using namespace std;

/*
In this class we scan every line in our file and convert him to flower.
*/
class MyFileReader
{
private:
    /*
    Our garden.
    */
    vector<Flower> m_myGarden;
    /*
    The file we scan.
    */
    ifstream m_myFile;
public:
    /*
    path - the csv file we want to open.
    we check this things:
    first, file is not excel type.
    second, file not open succesfully.
    third, empty file.
    Constructor
    */
    MyFileReader();
    /*
    This function scan every line in the excel file- every line is actually a flower.
    All the lines we scan is part of our garden, namely each line is a flower.
    */
    vector<Flower> getGarden();
    /*
    Destructor
    */
   ~MyFileReader();
    /*
    This function load the path.
    */
    void load(string path);
};

#endif
