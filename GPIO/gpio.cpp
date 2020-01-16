#include "gpio.h"

gpio::gpio(int p) {
	port = p; //GPIO number
	direction = get_direction(); // 1 is in and 0 is out
	value = get_value();
}

int gpio::get_direction() {
	string direction_file = GPIO_FOLDER; //GPIO_FOLDER is the default folder for GPIO
	direction_file += to_string(port); //add the GPIO port number in the end
	direction_file += "/direction"; //add the file name in the end
	ifstream is(direction_file); //open up a new input file stream 
	string temp_direction; //This temp vairable store the value we get from reading the file.
	if (is) { is >> temp_direction;}
	is.close();
	if(temp_direction == "in"){ //update the direction value
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
	string direction_file = GPIO_FOLDER;
	direction_file += to_string(port);
	direction_file += "/direction"; //get the file path
	ofstream is(direction_file,ios::trunc | ios::out); //open up the file with truncate option
	if (d == 1) {is << "in";} //update the file with in or out based on the input
	if (d == 0) {is << "out";}
	is.close();
	if (d == get_direction()) {return true;} //double check if we actually changed the value or not
	else {cout << "ERROR, port: " << port << " direction has not changed!" << endl;}
	return false;
}

bool gpio::set_value(int v) {
	if (v != 1 && v != 0) return false;
	if (get_direction() == 1) return false;
	string value_file = GPIO_FOLDER;
	value_file += to_string(port);
	value_file += "/value";
	ofstream is(value_file, ios::trunc | ios::out);
	is << v;
	is.close();
	if(v != get_value()) return false;
}
