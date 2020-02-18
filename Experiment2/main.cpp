#include <wiringPi.h>
#include <string>
#include <iostream>

using namespace std;
void send_char(char a){
	char temp = 0b00000001;
	digitalWrite(2,LOW);
	delayMicroseconds(95);

	for(int i = 0; i< 8;i++){
		if(temp & a){
		digitalWrite(2,HIGH);	
		}
		else{
		digitalWrite(2,LOW);
		}
		temp = temp << 1;
		delayMicroseconds(95);
	}
	digitalWrite(2,HIGH);
}
int main(){
	wiringPiSetupGpio();
	while(1){
		digitalWrite(2,HIGH);
		digitalWrite(2,LOW);
	}



delay(500);
char temp = 0b00000000;
cout << "lucio" << endl;
return 0;
}
