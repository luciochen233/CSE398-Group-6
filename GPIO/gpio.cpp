#include "gpio.h"


gpio::gpio(int p) {
	port = p;
	direction = get_direction(); // 1 is in and 0 is out
	value = get_value();
}
int gpio::get_direction() {
	string direction_file = GPIO_FOLDER;
	direction_file += to_string(port);
	direction_file += "/direction";
	ifstream is(direction_file);
	string temp_direction;
	if (is) { is >> temp_direction;}
	is.close();
	//cout << port << " direction is " << temp_direction << endl;
	if(temp_direction == "in"){
		direction = 1;
		return 1;
	} 
	if(temp_direction == "out") {
		direction = 0;
		return 0;
	}
}

int gpio::get_value() {
	string value_file = GPIO_FOLDER;
	value_file += to_string(port);
	value_file += "/value";
	ifstream is(value_file);
	if (is) { is >> value;}
	is.close();
	return value;
}

bool gpio::set_direction(int d) {
	//if (d != 1 && d != 0) return false;
	//if (d == get_direction()) return true;
	string direction_file = GPIO_FOLDER;
	direction_file += to_string(port);
	direction_file += "/direction";
	//cout << port<< " direction : " << direction_file << endl;
	ofstream is(direction_file,ios::trunc | ios::out);
	if (d == 1) {is << "in";}
	if (d == 0) {is << "out";}
	is.close();
	if (d == get_direction()) {return true;}
	else {cout << "ERROR, port: " << port << " direction has not changed!" << endl;}
	return false;
}

bool gpio::set_value(int v) {
	if (v != 1 && v != 0) return false;
	if (get_direction() == 1) return false;
	string value_file = GPIO_FOLDER;
	value_file += to_string(port);
	value_file += "/value";
	//cout << port<< " value : " << value_file << endl;
	ofstream is(value_file, ios::trunc | ios::out);
	is << v;
	is.close();
	//if (v == get_value()) { return true; }
	//else { cout << "ERROR, port: " << port << " value is not changed" << endl; }
}
