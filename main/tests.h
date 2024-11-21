#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"

void test_outputs(bool wheels = false) { // looping function
  set_nlsp(wheels); // TURN OFF WHEELS

  while(true) {
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
}

void test_pd() {
  if 
}
