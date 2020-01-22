#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

constexpr int PIN_MAX = 80;
constexpr char ADC_FOLDER[] = "/sys/bus/iio/devices/iio:devices0";

class adc {
	int port;
	int value;
public:
	adc(int);
	int get_value(int);
    ~adc(){}
};
