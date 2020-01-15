#include "pwm.h"  

pwm::pwm(int p) {
    if( p!=0 ) p = 0; // it only support pwm-0:0
    port = p;
    home_folder = PWM_FOLDER;
    home_folder += "-0:0/"; // it only support pwm-0:0
}

int pwm::get_capture(){
    // string capture_file = home_folder;
    // capture_file += "capture";
    // ifstream is(capture_file);
	// if (is) { is >> capture;}
	// is.close();
	return capture;
}
int pwm::get_duty_cycle(){
    string duty_cycle_file = home_folder;
    duty_cycle_file += "duty_cycle";
    ifstream is(duty_cycle_file);
	if (is) { is >> duty_cycle;}
	is.close();
	return duty_cycle;
}
int pwm::get_enable(){
    string enable_file = home_folder;
    enable_file += "enable";
    ifstream is(enable_file);
	if (is) { is >> enable;}
	is.close();
	return enable;
}
int pwm::get_period(){
    string period_file = home_folder;
    period_file += "period";
    ifstream is(period_file);
	if (is) { is >> period;}
	is.close();
	return period;
}
int pwm::get_polarity(){
    string polarity_file = home_folder;
    polarity_file += "polarity";
    ifstream is(polarity_file);
	if (is) { is >> polarity;}
	is.close();
	return polarity;
}
int pwm::get_uevent(){
    string uevent_file = home_folder;
    uevent_file += "uevent";
    ifstream is(uevent_file);
	if (is) { is >> uevent;}
	is.close();
	return uevent;
}

bool pwm::set_capture(int){ //don't touch
    return false;
}
bool pwm::set_uevent(int){
    return false;
}

bool pwm::set_duty_cycle(int v){
    string duty_cycle_file = home_folder;
	duty_cycle_file += "duty_cycle";
	ofstream is(duty_cycle_file, ios::trunc | ios::out);
	is << v;
	is.close();
}
bool pwm::set_enable(int v){
    string enable_file = home_folder;
	enable_file += "duty_cycle";
	ofstream is(enable_file, ios::trunc | ios::out);
	is << v;
	is.close();
}
bool pwm::set_period(int v){
    string period_file = home_folder;
	period_file += "period";
	ofstream is(period_file, ios::trunc | ios::out);
	is << v;
	is.close();
}
bool pwm::set_polarity(int v){
    string polarity_file = home_folder;
	polarity_file += "polarity";
	ofstream is(polarity_file, ios::trunc | ios::out);
	is << v;
	is.close();
}
