#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

constexpr int PIN_MAX = 80;
constexpr char GPIO_FOLDER[] = "/sys/class/gpio/gpio";

class gpio {
	int port;
	int direction;
	int value;
public:
	gpio(int);
	int get_direction();
	int get_value();
	bool set_direction(int);
	bool set_value(int);
    ~gpio(){}
};
