#ifndef DEFAULTIO_H
#define DEFAULTIO_H
#include <string>

using namespace std;

/*
abstract class that represent the way of communication
*/
class DefaultIO {
private:
public:
    /*
    data - the data i want to send
    the function send data by her way of communication
    */
    virtual void write(string data) = 0;
    /*
    the function get data by her way of communication
    */
    virtual string read() = 0;
};

#endif