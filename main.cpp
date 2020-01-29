#include "gpio.h"
#include "pwm.h"
#include "adc.h"
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

void old_main(){
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
}

void task3(){
	adc adc1(0);
	adc1.get_value();
	
	cout<<"the voltage is: " << adc1.get_value() << endl;
}

// void switch_color(int opacity){
	
// 	pwm pwm0(0);
// 	pwm pwm1(1);
// 	pwm1.set_enable(0);
// 	pwm pwm2(2);
// 	pwm2.set_enable(0);
// 	pwm0.set_duty_cycle((double)knob/4096*1000000);
// 	pwm1.set_duty_cycle((double)knob/4096*1000000);
// 	pwm2.set_duty_cycle((double)knob/4096*1000000);

// 	//std::this_thread::sleep_for (std::chrono::seconds(1));
// 	cout << "0duty_cycle " << pwm0.get_duty_cycle() << endl;
// 	cout << "enable " << pwm0.get_enable() << endl;
// 	cout << "1duty_cycle " << pwm1.get_duty_cycle() << endl;
// 	cout << "enable " << pwm1.get_enable() << endl;
// 	cout << "2duty_cycle " << pwm2.get_duty_cycle() << endl;
// 	cout << "enable " << pwm2.get_enable() << endl;

// }

int main() {

	adc adc1(0);
	gpio g73(73);
	g73.set_direction(1);
	
	pwm pwm0(0);
	pwm pwm1(1);
	pwm pwm2(2);

	int color = 0;
	int press = 0;
	int counter = 0;
	while(1){
		int knob = adc1.get_value();
		//cout << knob << endl;
		if(g73.get_value() == 1 && press == 0){
			press = 1;
			
			switch(color){
				case 0: pwm0.set_enable(1); pwm1.set_enable(0); pwm2.set_enable(0); color = 1; break;
				case 1: pwm0.set_enable(0); pwm1.set_enable(1); pwm2.set_enable(0); color = 2; break;
				case 2: pwm0.set_enable(0); pwm1.set_enable(0); pwm2.set_enable(1); color = 0; break;
			}
			

			cout << "push" << endl;
		}
		else if (g73.get_value() == 0){
			press = 0;
		}

		pwm0.set_duty_cycle((double)knob/4096*1000000);
		pwm1.set_duty_cycle((double)knob/4096*1000000);
		pwm2.set_duty_cycle((double)knob/4096*1000000);

		cout << "0duty_cycle " << pwm0.get_duty_cycle() << endl;
		cout << "enable " << pwm0.get_enable() << endl;
		cout << "1duty_cycle " << pwm1.get_duty_cycle() << endl;
		cout << "enable " << pwm1.get_enable() << endl;
		cout << "2duty_cycle " << pwm2.get_duty_cycle() << endl;
		cout << "enable " << pwm2.get_enable() << endl;
		cout << g73.get_value() << endl;
		cout << counter++ << endl;
		std::this_thread::sleep_for (std::chrono::seconds(1));

	}
	

	

	
	return 0;
}