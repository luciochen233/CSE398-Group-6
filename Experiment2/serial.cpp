#include <wiringPi.h>
#include <wiringSerial.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

vector<char> decode(vector<char> buff) {
	int position = 0;
	int value = -1;
	while(value != 0){
		value = buff[position];
		buff[position] = 0;
		position += value;
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
	char convert[4];
	for(int i = 1; i< buff.size() - 1; i+=4){
		convert[0] = buff[i];
		convert[1] = buff[i+1];
		convert[2] = buff[i+2];
		convert[3] = buff[i+3];
		temp.push_back((float)convert);
	}
	return temp;
}

vector<float> do_everything(int fd){
	vector<char> temp = get_char_array(fd);
	temp = decode(temp);
	return char_to_float(temp);
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
