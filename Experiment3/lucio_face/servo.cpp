#include "servo.h"

servo::servo(int p, int d){
    // i2cset -y 1 0x40 0x00 0x11
    // i2cset -y 1 0x40 254 0x7f
    // i2cset -y 1 0x40 0x00 0x81
    fd = wiringPiI2CSetup(0x40);
    setPort(p);
    setDegree(d);
    
}

int servo::getPort(){
    return port;
}

void servo::setPort(int p){
    if(p<0 || p>16){
        port = -1;
    }
    else{
        port = p;
    }
    offset = 0+4*port;
    wiringPiI2CWriteReg8(fd,0x00,0x11);
    wiringPiI2CWriteReg8(fd,254,0x7f);
    wiringPiI2CWriteReg8(fd,0x00,0x81);
    
}

int servo::getDegree(){
    //TODO
    //int fd = wiringPiI2CSetup(0x40);
    
    return degree;
}

void servo::setDegree(int d){
    degree = d;
    setPosition();
}

void servo::setDegree(float d){
    degree = d;
    setPosition();
}

void servo::setPosition(){
    //70 00 is the smallest 180 looking up
    //d8 01 is the biggest  180 looking down
    // there are 360 steps

    if (degree <0 || degree >180) return;
    float temp = degree *2;
    //i2cset -y 1 0x40 0x09 0x00
    //i2cset -y 1 0x40 0x08 0xcc  #this is 1ms
    //int fd = wiringPiI2CSetup(0x40);
    int H = ((int)temp+0x68)/0xff;
    int L = ((int)temp+0x68)%0xff;
    wiringPiI2CWriteReg8(fd,0x09+offset,H);
    wiringPiI2CWriteReg8(fd,0x08+offset,L);
    
    return;
}

