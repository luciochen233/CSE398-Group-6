#include <iostream>
#include <string>
#include "servo.h"
#include <cerrno>
#include <cstring>
#include <clocale>
using namespace std;


void test1(){
    int fd = wiringPiI2CSetup(0x40);
    if(fd == -1){
        cout << "can't get fd" << endl;
        exit(0);
    }
    cout << "fd is " << fd << endl;
    int ok = wiringPiI2CWriteReg8(fd,0x00,0x01);
    if(ok < 0){
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
    }
    cout << "ok is " << ok << endl;

    cout << "read" << wiringPiI2CReadReg8(fd,0x00) ;
    // wiringPiI2CWriteReg16(fd,254,0x7f);
    // wiringPiI2CWriteReg16(fd,0,0x81);
    // wiringPiI2CWriteReg16(fd,9,2);
    // wiringPiI2CWriteReg16(fd,8,0x30);
}
int main(){
    servo s1(0,90);
    servo s2(1,90);
    float i = 90;

    bool incre;

    float v = 2.5;
    while(1){
        if(i>=180){
            incre = false;
        }
        if(i<= 0){
            incre = true;
        }
        if(incre){
            i += v;
            s1.setDegree(i);
            s2.setDegree(i);
        }
        else{
            i -= v;
            s1.setDegree(i);
            s2.setDegree(i);
        }
        delay(100);
    }
    cout << "input degree" << endl;
    int user;
    cin >> user;
    s1.setDegree(user);

    cout << "input degree 2" << endl;
    //int user;
    cin >> user;
    s2.setDegree(user);
    return 0;
}