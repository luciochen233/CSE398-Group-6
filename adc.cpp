#include "adc.h"

adc::adc(int p) {
	port = p; //ADC number
	value = 0;
	value = get_value();// this is the value of the voltage
}

int adc::get_value() {
	string value_file = ADC_FOLDER;
	value_file += "/in_voltage0_raw";
	ifstream is(value_file);
	if (is) { is >> value; }
	is.close();
	return value;
}
