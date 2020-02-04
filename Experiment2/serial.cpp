#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void get_serial(){
	int fd = serialOpen("/dev/serial0",9600);
	while(1){
			cout << (char)serialGetchar(fd) << endl;
	}
}
int main(){
	get_serial();
	int fd = serialOpen("/dev/serial0", 9600);
	if(fd <1) cout << "fd is worng " << fd << endl;
	char temp = 0;

	while(1){
		if(serialDataAvail(fd)){
		       	char te = serialGetchar(fd);
			cout << te;
	
			serialPutchar(fd,te);
		}
	}

cout << "lucio" << endl;
return 0;
}
