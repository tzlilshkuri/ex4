#include "Distance.h"

/*
Constructor
*/
Distance::Distance() {
    
}

/*
v1 - vector of doubles
v2 - vector of doubles
the function return the Chebyshev distance of v1 and v2
*/
double Distance::chebyshevDistance(vector<double> v1, vector<double> v2) {
    double max = abs(v1[0] - v2[0]);
    for (int i = 1; i < v1.size(); i++) {
        if (abs(v1[i] - v2[i]) > max) {
            max = abs(v1[i] - v2[i]);
        }
    }
    return max;
}

/*
v1 - vector of doubles
v2 - vector of doubles
the function return the Canberra distance of v1 and v2
*/
double Distance::canberraDistance(vector<double> v1, vector<double> v2) {
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != 0 && v2[i] != 0) {
            sum += ((abs(v1[i] - v2[i])) / (abs(v1[i]) + abs(v2[i])));    
        }
    }
    return sum;
}

/*
v1 - vector of doubles
v2 - vector of doubles
p - const number that help to calculate the distance
the function return the Minkowski distance of v1 and v2
*/
double Distance::minkowskiDistance(vector<double> v1, vector<double> v2, double p) {
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += pow(abs(v1[i] - v2[i]), p);
    }
    return pow(sum, (1 / p));
}

