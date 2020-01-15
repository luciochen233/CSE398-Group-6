#include "gpio.h"
#include "pwm.h"
#include <thread>
#include <chrono>
using namespace std;



void task1(){
	gpio g67(67);
    gpio g66(66);

	cout << "66's value" << endl;
	int p66 = 0;
	cin >> p66;
    g66.set_direction(0); // 0 is out
    g66.set_value(p66);

	cin.get();
	cin.get();
	cout << "change 66's direction to input" << endl;
	g66.set_direction(1);
	cout << "hit enter when ready" << endl;
	cin.get();
	cin.get();
	cout << "the value for port 66 is : " << g66.get_value() << endl;
}

void task2(){
	gpio g66(66);
	g66.set_direction(0);
	while(1){
		g66.set_value(1);
		g66.set_value(0);
	}
}

int main() {
	pwm pwm0(0);
	cout << "duty_cycle " << pwm0.get_duty_cycle() << endl;
	cout << "enable " << pwm0.get_enable() << endl;
	cout << "period " << pwm0.get_period() << endl;
	cout << "polarity " << pwm0.get_polarity() << endl;
	while(1){
		pwm0.set_duty_cycle(200000);
		std::this_thread::sleep_for (std::chrono::seconds(1));
		pwm0.set_duty_cycle(400000);
		std::this_thread::sleep_for (std::chrono::seconds(1));
		pwm0.set_duty_cycle(600000);
		std::this_thread::sleep_for (std::chrono::seconds(1));
		pwm0.set_duty_cycle(800000);
		std::this_thread::sleep_for (std::chrono::seconds(1));
		pwm0.set_duty_cycle(1000000);
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
	

	
	return 0;
}