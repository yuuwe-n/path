#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"

void setup() {
  initialize();

  set_nlsp(false);
  duration(1);

  /*
  while (digitalRead(bump_5)){
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);
  digitalWrite(LED_RF, HIGH); // Turn the LED on
  }
  delay(500);
  */
}

void loop() {
}

  /* THIS WORKS
  bool s = digitalRead(bump_5);
  Serial.println(s);
  delay(500);
  */
  
  // digitalWrite(LED_RF, LOW); // Turn the LED on
  // output_data();
