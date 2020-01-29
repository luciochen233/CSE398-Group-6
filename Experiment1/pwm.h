#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
constexpr char PWM_FOLDER[] = "/sys/class/pwm/pwm";

class pwm{
	int port;
	int capture;
	int duty_cycle;
	int enable;
	int period;
	int polarity;
	int uevent;
    string home_folder;
public:
	pwm(int p);
    int get_capture();
    int get_duty_cycle();
    int get_enable();
    int get_period();
    int get_polarity();
    int get_uevent();

    bool set_capture(int);
    bool set_duty_cycle(int);
    bool set_enable(int);
    bool set_period(int);
    bool set_polarity(int);
    bool set_uevent(int);
};