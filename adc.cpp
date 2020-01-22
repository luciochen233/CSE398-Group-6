float Avr::Adc::readVolts 	(	uint8_t 	channel, 
uint8_t 	nsamples = 1 
)
/*
//not the code that we should use but can use the concepts to build the file 
#include <mosaic/allqed.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#ifdef __GNUC__
// For PDQ line platforms, the driver is enabled by simply including
// the header file below.
#include <waim.h>
#else
// For the QED/Q line platform, we include the kernel extension manager
// generated library.c. We assume that it is present in this directory.
#include "library.h"
#include "library.c"
#endif // __GNU__
 
 
// ******************* DEMONSTRATION PROGRAM ***************************
// This demonstration requires that you wire pins 14 and 18 together.  They can
// also be connected with a low value resistor.
// This program outputs 8 voltages and then reads them back.  For each measurement
// the error is calculated in bits.  At the end the average error is printed.
 
 
 
// NOTE: YOU MUST MAKE SURE THAT THIS CONSTANT MATCHES YOUR HARDWARE JUMPERS!!
#define WAIM_MODULE_NUM 0 // Make sure jumpers J1 and J2 are removed!!!
 
 
#define min(a,b) ((a)>(b)?(b):(a))
 
 
void set_channel6( int value )
{
  To_DAC12( value, DAC12_CH6, WAIM_MODULE_NUM);
}
 
unsigned int read_channel0( void )
{
  return AD16_Sample( AD16_CH0, WAIM_MODULE_NUM );
}
 
int main ( void )
{
  int i;
  unsigned output_counts, input_counts;
  float output_voltage, input_voltage, error, bits_error;
 
  printf("\n\nWelcome to the Analog I/O Wildcard demo!\n");
  printf("This demo requires pins 14 and 18 to be connected\n");
  printf("Press any key to start...\n");
  Key();
  printf("\n");
 
  // Init DAC to use 2.048 int ref.  This must be done before any outputs are made
  Init_Analog_IO(INT_2V_DAC12,WAIM_MODULE_NUM);
 
  // Set to 0.  This variable is added to in the for loop
  bits_error = 0;
 
  for(i = 1; i < 9; i++ )
  {
      // we use min to insure we stay within the bounds of the DAC
      output_counts = min( 4095, 512*i );
 
      // output voltage to dac channel 6
      set_channel6( output_counts );
 
      // wait one millisecond
      MicrosecDelay( 1000 );
 
      // read the voltage from channel 0
      input_counts = read_channel0();
 
      // calcualte float values in Volts
      output_voltage = 2.048*(output_counts/2048.0);
      input_voltage = ( input_counts / 65536.0 ) * 4.096;
 
      // calculate error
      error = fabs(output_voltage-input_voltage);
 
      // the error in bits is: the error divided by the value of one bit
      bits_error += error / 0.001;
 
      printf("Output %2.3f volts.  Read back %2.4f volts.\n", output_voltage, input_voltage);
 
  }
 
  bits_error = bits_error / 8;
  printf("Over 8 measurements there was an average absolute error of %1.1f bits.\n", bits_error);
 
    return 0;
 
 
}

*/
