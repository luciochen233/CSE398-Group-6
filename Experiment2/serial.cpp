#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

void get_serial(){
	int fd = serialOpen("/dev/serial0",9600);
	while(1){
		cout << (char)serialGetchar(fd) << endl;
	}
}
vector<char> decode(vector<char> buff) {
	int decode = 0;
	int next_decode = 0;
	decode = buff[decode];
	while(decode != 0){
		next_decode = buff[decode];
		buff[decode]=0;
		decode = next_decode;
		next_decode = 0;
	}
	return buff;
}

vector<char> get_char_array(int fd){
	vector<char> temp;
	int size = 0;
	while(serialDataAvail(fd)){
		char te = serialGetchar(fd);
		temp.push_back(te);
		if(te == 0x00) return temp;
		size++;
		if(size > 100) return temp;
	}
	return temp;
}

vector<float> char_to_float(vector<char> buff){
	vector<float> temp;
	byte convert[4];
	for(int i = 1; i< buff.size() - 1; i+=4){
		convert[0] = buff[i];
		convert[1] = buff[i+1];
		convert[2] = buff[i+2];
		convert[3] = buff[i+3];
		temp.push_back((float)convert)
	}
	return temp;
}

vector<float> do_everything(int fd){
	vector<char> temp = get_char_array(fd);
	temp = decode(temp);
	return char_to_float(temp);
}

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

int main(){
	//get_serial();
	int fd = serialOpen("/dev/serial0", 9600);
	if(fd <1) cout << "fd is worng " << fd << endl;
	char temp = 0;
	while(1){
		if(serialDataAvail(fd)){
			delay(400);
			vector<float> l1 = do_everything(fd);
			for(auto i: l1){
				cout << i << " " << endl;
			}
		}
	}

	cout << "This is the end" << endl;
	return 0;
}
