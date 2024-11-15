#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"

void setup() {
  initialize();
}

int calc_error(uint16_t input[8]) { // takes input of sensor values

/*
 * Negative error : black line is to the left => ERROR = -40mm => error < 0 : steer to the left
 * Positive error : black line is to the right => ERROR = 40mm => error > 0 : steer to the right
 */
  
  int error;
  int weighted_sum = 0;
  int temp[8]={0,0,0,0,0,0,0,0};
  
  for (int i = 0; i < 8; i++) {
    temp[i] = input[i] - mins[i];
    if (temp[i] <=0) {
      temp[i]=0;
    } 
    temp[i] = temp[i] * 1000 / maxs[i];
    weighted_sum += temp[i] * weights[i];
  }
  error = weighted_sum / 8;

  store_data(error); // MAY NEED TO REMOVE IN DRIVING
  
  return error;
}

int calc_p(int error) {
  int p = K_P * abs(error);
  return p;
}

int calc_d(int error, int prev_error) {
  int d = K_D * abs(error - prev_error);
  return d;
}

int* control_car(int error, int prev_error = 0) {
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   static int pwm[2]; // [0] is left_pwm, [1] is right_pwm

   int p = calc_p(error);
   int d = calc_d(error, prev_error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p; // Speed up left wheel
      r_speed = base_speed - p; // Slow down right wheel                  
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p; // Slow down left wheel
      r_speed = base_speed + p; // Speed up right wheel
    }

   prev_error = error;

  //l_speed = constrain(l_speed, 0, max_speed);
  //r_speed = constrain(r_speed, 0, max_speed);
  
  analogWrite(left_pwm_pin, l_speed);
  analogWrite(right_pwm_pin, r_speed);

  // return pwm speeds
  pwm[0] = l_speed;
  pwm[1] = r_speed;
  return pwm;
}

void test_outputs(bool wheels = false) { // this function should loop
  
  set_nlsp(wheels); // TURN OFF WHEELS
  
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);

  int* pwm = control_car(error);
  int left_pwm = pwm[0];
  int right_pwm = pwm[1];

  Serial.print(left_pwm);
  Serial.print("\t | \t");

  Serial.print(right_pwm);
  Serial.print("\t | \t");

  Serial.print(error);
  Serial.print("\t | \t");
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensor_values[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(500);
}

void drive() {
  set_forward();
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);
  control_car(error);
}

// START HERE AND TEST YOUR STORE_DATA FUNCTION

const int DATA_COUNT = 1500;
short count = 0;
short data[DATA_COUNT];

void store_data(int error) {
  data[count] = error;
  count += 1;
}

unsigned long startTime;
const unsigned long delayTime = 10000;
void test_store_data() {
  drive();
  if (millis() - startTime >= delayTime) {
        stop_car();      // Call the function after 10 seconds
        startTime = millis();  // Reset startTime if you want to call the function every 10 seconds
  }
}

void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i]); Serial.print('\t');
      }
    }
  }
}

void stop_car() {
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
  analogWrite(LED_RF, HIGH); // turn on yellow LED 

  output_data();
}

void duration(int max_revs){ // stops after number of revolutions
  if (revs() <= max_revs){
    stop_car();
    return;
  }
  drive();
}

void loop() {
  //test_outputs(false);
  //drive();
  
}

  /* TODO:
   *  - test wheel direction / variable names for left/right XXX done?
   *  - test store_data
   *  - test stop_car
   *  - test output_data
   *  - test duration
   *  - 180 degree function
   *  - 360 degree donut function
   *  - bump => change k_p, k_d
   *  - watch out for void, and global variables, when doing multiple files
   *  - CHECK SET_LEFT, SET_RIGHT FUNCTIONS
   *  - OTHER LEDS
   */
