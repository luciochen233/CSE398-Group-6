#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class cobs_float_array {
 private:
  vector<char> buff;
  vector<float> result;
  int fd;
  bool ava;
  void read_stream();
  void decode();
  void translate();

 public:
  cobs_float_array();
  ~cobs_float_array() { serialClose(fd); }
  void read();
  void send();

  vector<float> getData() {ava = false; return result; }
  bool avaliable() { return ava; }

  friend ostream &operator<<(ostream &os, const cobs_float_array &arr);
};

  void cobs_float_array::send(){
	  uint8_t b[3];
	  b[0] = 0x02;
	  b[1] = 'h';
	  b[2] = 0x00; 
	//serialPrintf (fd, b);
	serialPutchar ( fd, 0x02) ;
	serialPutchar ( fd, 'h') ;
	serialPutchar ( fd, 0x00) ;
  }

void cobs_float_array::read() {
  read_stream();
  decode();
  translate();
}

cobs_float_array::cobs_float_array() {
  fd = serialOpen("/dev/serial0", 9600);
  if (fd < 1) cout << "fd is worng " << fd << endl;
  ava = false;
}

void cobs_float_array::read_stream() {
  while (serialDataAvail(fd)) {
    char te = serialGetchar(fd);
    buff.push_back(te);
    if (te == 0x00) {
      ava = true;
      return;
    }
    if (buff.size() > 256) {
      buff.clear();
      ava = false;  // this indicates a read data error
    }
  }
}

void cobs_float_array::decode() {  // after decode, the first and last byte
                                   // should be zero
  if (!ava) return;
  int position = 0;
  int value = -1;
  while (value != 0) {
    value = buff[position];
    buff[position] = 0;
    position += value;
    if (position > buff.size()) {
      ava = false;  // this indicates a read data error
      buff.clear();
      return;
    }
  }
}

void cobs_float_array::translate() {
  if (!ava) return;
  if(!result.empty()) result.clear();
  if(buff.size() < 7){
	buff.clear();
	ava = false;
	send();
	return;
  }
  char convert[4];
  for (int i = 1; i < buff.size() - 1; i += 4) {
    convert[0] = buff[i];
    convert[1] = buff[i + 1];
    convert[2] = buff[i + 2];
    convert[3] = buff[i + 3];
    result.push_back(*(float *)convert);
  }
  buff.clear();
}

ostream &operator<<(ostream &os, const vector<float> &f1) {
  for (auto f : f1) {
    os << f << ", ";
  }
  os << endl;
  return os;
}

int main() {
  cobs_float_array arr1;
  while (1) {
    arr1.read();
    if (arr1.avaliable()) {
      vector<float> temp = arr1.getData();
      cout << temp << endl;
    }
  }

  cout << "This is the end" << endl;
  return 0;
}
