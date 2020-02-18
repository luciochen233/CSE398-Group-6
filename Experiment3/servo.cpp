#include "servo.h"
servo::servo(){
    setPort(0);
}

servo::servo(int p){
    setPort(p);
}

servo::servo(int p, int d){
    // i2cset -y 1 0x40 0x00 0x11
    // i2cset -y 1 0x40 254 0x7f
    // i2cset -y 1 0x40 0x00 0x81
    setPort(p);
    setDegree(d);
}

int servo::getPort(){
    return port;
}

void servo::setPort(int p){
    offset = 0+4*p;
    int fd = wiringPiI2CSetup(0x40);
    wiringPiI2CWriteReg8(fd,0x00,0x00);
    wiringPiI2CWriteReg8(fd,254,0x7f);
    wiringPiI2CWriteReg8(fd,0x00,0x81);
    if(p<0 || p>16){
        port = -1;
    }
    else{
        port = p;
    }
}

int servo::getDegree(){
    //TODO
    //int fd = wiringPiI2CSetup(0x40);
    
    return degree;
}

void servo::setDegree(int d){
    //70 00 is the smallest 180 looking up
    //d8 01 is the biggest  180 looking down
    // there are 360 steps

    if (d<0 || d>180) return;
    degree = d;
    //i2cset -y 1 0x40 0x09 0x00
    //i2cset -y 1 0x40 0x08 0xcc  #this is 1ms
    int fd = wiringPiI2CSetup(0x40);
    d*=2;
    int H = (d+0x68)/0xff;
    int L = (d+0x68)%0xff;
    wiringPiI2CWriteReg8(fd,0x09+offset,H);
    wiringPiI2CWriteReg8(fd,0x08+offset,L);
    
    return;
}

