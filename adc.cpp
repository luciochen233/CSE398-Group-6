#include "adc.h"

adc::adc(int p) {
	port = p; //ADC number
	value = get_value();// this is the value of the voltage
}

int adc::get_value() {
	string value_file = ADC_FOLDER;
	value_file += to_string(port);
	value_file += "/value";
	ifstream is(value_file);
	if (is) { is >> value; }
	is.close();
	return value;
}
