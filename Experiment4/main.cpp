#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

int main(){
    wiringPiSetup();
    wiringPiSetupGpio();

    cout << "lucio" << endl;
    softPwmCreate(2,50,100);
    int duty = 0;
    bool inc = true;
    while(1){
        if(inc){
            softPwmWrite(2,duty++);
        }
        else{
            softPwmWrite(2,duty--);
        }
        if(duty < 0){
            inc = true;
        }
        if(duty > 100){
            inc = false;
        }
        
        delay(10);
    }

    return 0;
}