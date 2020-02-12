#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
float get_float(int fd){
	char buf[6];
	int r_size = 0;
	float flo = -1;
	while(serialDataAvail(fd)){
		char te = serialGetchar(fd);
		buf[r_size] = te;
		r_size++;
		if(te == 0x00){
			cout << "We got data" << endl;
			flo = *(float*)(buf+1);
			//switch(r_size){
			//	case 6: flo = *(float*)(buf+1);
			cout << flo << endl;
			//break;
			//}
			cout << "size is " << r_size << endl;
			return flo;
		}
		if(r_size == 6) return -1.1;
	}
	return -1;
}
vector<float> get_float_array(int fd){
	char buf[42];
	int r_size = 0;
	vector<float> l1;
	float* flo;
	while(serialDataAvail(fd)){
		char te = serialGetchar(fd);
		buf[r_size] = te;
		r_size++;
		if(te == 0x00){
			cout << "We got data" << endl;
			flo = (float*)(buf+1);
			cout << "size is " << r_size << endl;
			for(int i = 0; i< 10; i++){
				l1.push_back(flo[i]);
			}
			return l1;
		}
		if(r_size == 42) return l1;
	}
	return l1;
}

void get_serial(){
	int fd = serialOpen("/dev/serial0",9600);
	while(1){
		cout << (char)serialGetchar(fd) << endl;
	}
}