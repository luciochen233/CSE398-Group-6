//Author: Guoliang Chen 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;

constexpr char file_name[] = "C:\\cpptemp\\test.txt";
constexpr int PIN_MAX = 80;
constexpr char GPIO_FOLDER[] = "/sys/class/gpio/gpio";
class gpio {
	int port;
	int direction;
	int value;
public:
	gpio(int p) {
		port = p;
		direction = get_direction(); // 1 is in and 0 is out
		value = get_value();
	}
	int get_direction() {
		string direction_file = GPIO_FOLDER;
		direction_file += to_string(port);
		direction_file += "/direction";
		ifstream is(direction_file);
		if (is) { is >> direction;}
		is.close();
		return direction;
	}

	int get_value() {
		string value_file = GPIO_FOLDER;
		value_file += to_string(port);
		value_file += "/value";
		ifstream is(value_file);
		if (is) { is >> value;}
		is.close();
		return value;
	}

	bool set_direction(int d) {
		if (d != 1 && d != 0) return false;
		if (d == get_direction()) return true;
		string direction_file = GPIO_FOLDER;
		direction_file += to_string(port);
		direction_file += "/direction";
		ofstream is(direction_file,ios::trunc | ios::out);
		if (d == 1) {is << "in";}
		if (d == 2) {is << "out";}
		if (d == get_direction()) {return true;}
		else {cout << "ERROR, direction has not changed!" << endl;}
		return false;
	}

	bool set_value(int v) {
		if (v != 1 && v != 0) return false;
		if (get_direction() == 1) return false;
		string value_file = GPIO_FOLDER;
		value_file += to_string(port);
		value_file += "/value";
		ofstream is(value_file, ios::trunc | ios::out);
		is << v;
		is.close();
		if (v == get_value()) { return true; }
		else { cout << "ERROR, value is not changed" << endl; }
	}

};

int main() {
	
	ofstream out_file(file_name,ios::trunc|ios::out);
	out_file << "out";
	if (out_file) { cout << "write OK" << endl; }
	else { cout << "write False" << endl; }
	out_file.close();

	//cout << "write lucio to file "<< file_name << endl;

	return 0;
}