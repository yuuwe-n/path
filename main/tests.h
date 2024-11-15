#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"

void test_outputs(bool wheels = false) { // does not rely on loop()
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

unsigned long startTime;
const unsigned long delayTime = 10000;
void test_store_data() {
  drive_car();
  if (millis() - startTime >= delayTime) {
        stop_car();      // Call the function after 10 seconds
        startTime = millis();  // Reset startTime if you want to call the function every 10 seconds
  }
}
