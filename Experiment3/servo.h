#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <string>
#include <vector>

class servo{
private:
    int port;
    int degree;
    int offset;
public:
    servo();
    ~servo(){};
    servo(int p);
    servo(int p, int d);
    int getPort();
    void setPort(int p);
    int getDegree();
    void setDegree(int d);
};