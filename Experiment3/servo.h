#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <string>
#include <vector>

class servo{
private:
    int port;
    float degree;
    int offset;
    int fd;
    void setPosition();
public:
    ~servo(){};
    servo(int, int);
    int getPort();
    void setPort(int);
    int getDegree();
    void setDegree(int);
    void setDegree(float);

};