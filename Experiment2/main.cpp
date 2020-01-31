#include <wiringPi.h>
#include <string>
#include <iostream>

using namespace std;
int main(){
	wiringPiSetupGpio();
pinMode(2,OUTPUT);
delay(500);
while(1){
digitalWrite(2,HIGH);
digitalWrite(2,LOW);

}
cout << "lucio" << endl;
return 0;
}
