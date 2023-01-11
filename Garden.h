#ifndef GARDEN_H
#define GARDEN_H

#include <vector>
#include <string>
#include "Flower.h"
#include "MyFileReader.h"

using namespace std;

/*
this class have all the lines in the file each line is represnt by flower
and the members are:
m_ flowers - vector of flowers that contains all the flowers in the file
m_myFileReader - a pointer to a file
*/
class Garden {
private:
    vector<Flower> m_flowers;
    MyFileReader m_myFileReader;
public:
    /*
    path - a path to csv file
    constructor
    */
    Garden();
    /*
    the function return the number of the attributes of flowers
    */
    int getSizeAtt();
    /*
    flower - the flower i want to calculate the distance to
    k - numer of the closest flower
    calc - by which calculator i want to use
    the method return the k closest flower in vector
    */
    vector<Flower> getKSmallest(Flower flower, int k, string calc);
    /*
    path - a path to file
    this function load the path to file
    */
    void load(string path);
};

#endif