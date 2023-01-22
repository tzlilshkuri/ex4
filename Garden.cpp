#include "Garden.h"
#include "Flower.h"
#include "Distance.h"
#include <algorithm>
#include <stdexcept>

#define AUC_CALC 2
#define MAN_CALC 1
#define MIN_CALC 2

/*
constructor
*/
Garden::Garden() {
}

/*
path - a path to csv file
constructor
*/
void Garden::load(string path) {
    try {
        m_myFileReader.load(path);
        m_flowers = m_myFileReader.getGarden();
    }
    catch(invalid_argument& x) {
        throw;
    }
}


/*
the function return the number of the attributes of flowers
*/
int Garden::getSizeAtt() {
    return m_flowers[0].getAtrr().size();
}

/*
flowerGar - a flower from the gardan i want to claculate the distance between them
flowerCheck - a flower i want to check the distance from him to every flower in the garden
calc - by which calculator i want to use
*/
double calcDiss(Flower flowerGar, Flower flowerCheck, string calc) {
    Distance dis;
    if (calc == "AUC") {
        return dis.minkowskiDistance(flowerGar.getAtrr(), flowerCheck.getAtrr(), AUC_CALC);
    }
    if (calc == "MAN") {
        return dis.minkowskiDistance(flowerGar.getAtrr(), flowerCheck.getAtrr(), MAN_CALC);
    }
    if (calc == "CHB") {
        return dis.chebyshevDistance(flowerGar.getAtrr(), flowerCheck.getAtrr());
    }
    if (calc == "CAN") {
        return dis.canberraDistance(flowerGar.getAtrr(), flowerCheck.getAtrr());
    }
    if (calc == "MIN") {
        return dis.minkowskiDistance(flowerGar.getAtrr(), flowerCheck.getAtrr(), MIN_CALC);
    }
    return -1;
}

/*
flower - the flower i want to calculate the distance to
k - numer of the closest flower
calc - by which calculator i want to use
the method return the k closest flower in vector
*/
vector<Flower> Garden::getKSmallest(Flower flower, int k, string calc) {
    vector<Flower> smallK;
    for (int i = 0; i < m_flowers.size(); i++) {
        m_flowers[i].setDistance(calcDiss(m_flowers[i], flower, calc));
    }
    sort(m_flowers.begin(), m_flowers.end());
    for (int i = 0; i < k && i < m_flowers.size(); i++) {
        smallK.push_back(m_flowers[i]);
    }
    return smallK;
}