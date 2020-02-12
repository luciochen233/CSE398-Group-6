/* arduino side codes */
#include <PacketSerial.h>
#include <Math.h>
/*for bno055 sensor*/
#include <Wire.h>
//#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

PacketSerial_<COBS> ps;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
/* from example*/
double xPos = 0, yPos = 0, headingVel = 0;
uint16_t BNO055_SAMPLERATE_DELAY_MS = 10; //how often to read data from the board
uint16_t PRINT_DELAY_MS = 500; // how often to print the data
uint16_t printCount = 0; //counter to avoid printing every 10MS sample

//velocity = accel*dt (dt in seconds)
//position = 0.5*accel*dt^2
double ACCEL_VEL_TRANSITION =  (double)(BNO055_SAMPLERATE_DELAY_MS) / 1000.0;
double ACCEL_POS_TRANSITION = 0.5 * ACCEL_VEL_TRANSITION * ACCEL_VEL_TRANSITION;
double DEG_2_RAD = 0.01745329251; //trig functions require radians, BNO055 outputs degrees
float current_reading[10];
int current_i = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(A0,INPUT);
  ps.begin(9600);
  ps.setStream(&Serial1);
  ps.setPacketHandler(&onPacketReceived);
  
  //Wire.setSDA(38);
  //Wire.setSCL(37);
  Wire.begin();
  
  if(!bno.begin()){
    Serial.print("BNO is ERROR");
    while(1);
  }
}

void onPacketReceived(const uint8_t* buffer, size_t size)
{
    Serial.println((char*)buffer);
    if(*(char*)buffer == 'h'){
      send_float_array(current_reading, sizeof(current_reading));
    }
}

void send_float_array(float arr[], char s){
  ps.update();
  ps.send((byte *)arr,s);
}

void send_analog_reading(){
  float farr[10];
  for(int i = 0; i<10; i++){
    int measure = analogRead(A0);
    farr[i] = (float)measure / 1024 * 3.3;
    //Serial.println(farr[i]);
    delay(100);
  }
  send_float_array(farr, sizeof(farr));
}

void send_sensor_reading(){
  sensors_event_t event; 
  bno.getEvent(&event);
  float farr[10];
  for(int i = 0; i<10; i++){
    
    sensors_event_t orientationData , linearAccelData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    float x_acc = linearAccelData.acceleration.x;
    float y_acc = linearAccelData.acceleration.y;
    float z_acc = linearAccelData.acceleration.z;
  
    float res = x_acc*x_acc+y_acc*y_acc+z_acc*z_acc;
    res = sqrt(res);
    farr[i] = res;
    Serial.print(res);
    Serial.println();
    delay(100);
  }
  send_float_array(farr, sizeof(farr));
}

void loop() {
  ps.update();
  sensors_event_t orientationData , linearAccelData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    float x_acc = linearAccelData.acceleration.x;
    float y_acc = linearAccelData.acceleration.y;
    float z_acc = linearAccelData.acceleration.z;
  
    float res = x_acc*x_acc+y_acc*y_acc+z_acc*z_acc;
    res = sqrt(res);
    if(current_i <9){
      current_i++;
    }
    else{
      for(int i = 0; i<9;i++){
        current_reading[i] = current_reading[i+1];
      }
    }
    current_reading[current_i] = res;
    if(res > 3){
      Serial.print("OUCH");
      uint8_t temp[5] = "OUCH";
      ps.send(temp,4);
    }
    Serial.print(res);
    Serial.println();
    delay(100);
}
