#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>
#include <cmath>

using namespace std;

/*
the class calculate the distances between two vectors
*/
class Distance {
private:
public:
    /*
    constructor
    */
    Distance();
    /*
    v1 - vector of doubles
    v2 - vector of doubles
    the function return the Chebyshev distance of v1 and v2
    */
    double chebyshevDistance(vector<double> v1, vector<double> v2);
    /*
    v1 - vector of doubles
    v2 - vector of doubles
    the function return the Canberra distance of v1 and v2
    */
    double canberraDistance(vector<double> v1, vector<double> v2);
    /*
    v1 - vector of doubles
    v2 - vector of doubles
    p - const number that help to calculate the distance
    the function return the Minkowski distance of v1 and v2
    */
    double minkowskiDistance(vector<double> v1, vector<double> v2, double p);
};

#endif