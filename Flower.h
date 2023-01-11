#ifndef FLOWER_H
#define FLOWER_H

#include <vector>
#include <string>
using namespace std;

/*
this class represanted me a flower. a flower is reprasanted by vector of attributes of
flower and type in basicly and i add a distance to a flower i need to know his type
m_attributes - the attributes of the flower
m_type - the type of the flower
m_distance - the distance of this flower from the flower the user insert
*/
class Flower {
private:
    vector<double> m_attributes;
    string m_type;
    double m_distance;
public:
    /*
    line - the flower's atributes i want to separate 
    sep - the char that separate
    type - flower's type
    Constructor
    */
    Flower(string line, char sep, string type);
    /*
    the function return the flower's attributes
    */
    vector<double> getAtrr();
    /*
    the function return the flower's type
    */
    string getType();
    /*
    distance - the new distance
    the method update the distance of the flower
    */
    void setDistance(double distance);
    /*
    flowers - vector of the nearest flowers to this flower
    the nethod uptate the type of this flower by the most number of 
    shows of type
    */
    void updateType(vector<Flower> flowers);
    /*
    flower - flower i want to compare to
    the fonction rewrite the operand '>'
    */
    bool operator>(const Flower &flower) const;
    /*
    flower - flower i want to compare to
    the fonction rewrite the operand '<'
    */
    bool operator<(const Flower &flower) const;
};

#endif