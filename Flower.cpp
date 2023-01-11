#include "Flower.h"
#include "BuildVector.h"
#include <map>
#include <cstdlib>
#include <iostream>

/*
line - the flower's atributes i want to separate 
sep - a note that separate
type - flower's type
Constructor
*/
Flower::Flower(string line, char sep, string type) {
    BuildVector buildV;
    m_attributes = buildV.makeNewVector(line, sep);
    m_type = type;
    m_distance = -1;
}

/*
the function return the flower's type
*/
string Flower::getType() {
    return m_type;
}

/*
the function return the flower's attributes
*/
vector<double> Flower::getAtrr() {
    return m_attributes;
}

/*
distance - the new distance
the method update the distance of the flower
*/
void Flower::setDistance(double distance) {
    m_distance = distance;
}

/*
flowers - vector of the nearest flowers to this flower
the nethod uptate the type of this flower by the most number of 
shows of type
*/
void Flower::updateType(vector<Flower> flowers) {
    map<string, int> cntTypes;
    int max;
    string maxType;
    for (int i = 0; i < flowers.size(); i++) {
        if (cntTypes.find(flowers[i].getType()) == cntTypes.end()) {
            cntTypes.insert({flowers[i].getType(), 1});
        } else {
            cntTypes.find(flowers[i].getType())->second++;
        }
    }
    max = cntTypes.begin()->second;
    maxType = cntTypes.begin()->first;
    for (map<string, int>::iterator it = cntTypes.begin(); it != cntTypes.end(); it++) {
        if (max < it->second) {
            max = it->second;
            maxType = it->first;
        }
    }
    m_type = maxType;
}

/*
    flower - flower i want to compare to
    the fonction rewrite the operand '>'
*/
bool Flower::operator>(const Flower &flower) const {
    return m_distance > flower.m_distance;
}

/*
    flower - flower i want to compare to
    the fonction rewrite the operand '<'
*/
bool Flower::operator<(const Flower &flower) const {
    return m_distance < flower.m_distance;
}