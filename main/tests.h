#ifndef TESTS_H
#define TESTS_H

#include "data_collection.h"
#include "encoder.h"
#include "init.h"
#include "motor_control.h"
#include "pd_control.h"
#include "routines.h"

void test_encoder() {
  set_nlsp(true);
  analogWrite(left_pwm_pin, 40);
  analogWrite(right_pwm_pin, 40);
  Serial.print(avg_encoder());
  Serial.print('\t');
  Serial.print(revs());
  Serial.println();
}

int encoder_counts = 0;
int final_count = 0;
void test_rotation() {
  resetEncoderCount_left();
  resetEncoderCount_right();
  
  analogWrite(left_pwm_pin, 25);
  analogWrite(right_pwm_pin, 25);
  set_right();

  
  delay(2000);
  while(true) {
    encoder_counts = avg_encoder();
    if (!digitalRead(bump_5)){
      analogWrite(LED_Y, HIGH);
      stop_car();
      break;
    }
  }
  final_count = encoder_counts;

  while(true) {
    Serial.println(final_count);
  }

  delay(2000);
}


void test_outputs(bool nlsp = false) { // looping function
  set_nlsp(nlsp); // TURN OFF WHEELS

  while(true) {
    ECE3_read_IR(sensor_values);
    int error = calc_error(sensor_values);
  
    Serial.print(l_speed);
    Serial.print("\t | \t");
  
    Serial.print(r_speed);
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

void variate_kd() {
  if (!digitalRead(bump_5)) {
    K_D = 1.5;
  }
  if (!digitalRead(bump_4)) {
    K_D = 1.0;
  }
  if (!digitalRead(bump_3)) {
    K_D = 0.80;
  }
  if (!digitalRead(bump_2)) {
    K_D = 0.70;
  }
  if (!digitalRead(bump_1)) {
    K_D = 0.50;
  }
  if (!digitalRead(bump_0)) {
    K_D = 0.00;
  }
}

void variate_kp() {
  if (!digitalRead(bump_5)) {
    K_P = 0.085;
  }
  if (!digitalRead(bump_4)) {
    K_P = 0.080;
  }
  if (!digitalRead(bump_3)) { 
    K_P = 0.075;
  }
  if (!digitalRead(bump_2)) {  
    K_P = 0.070;
  }
  if (!digitalRead(bump_1)) { 
    K_P = 0.065;
  }
  if (!digitalRead(bump_0)) {
    K_P = 0.00;
  }
}

void variate_turn_scalar() {
  if (!digitalRead(bump_5)) {
    TURN_SCALAR = 0.80;
  }
  if (!digitalRead(bump_4)) {
    TURN_SCALAR = 0.70;
  }
  if (!digitalRead(bump_3)) {
    TURN_SCALAR = 0.60;
  }
  if (!digitalRead(bump_2)) {
    TURN_SCALAR = 0.50; // this iss ur minimum about the best
  }
  if (!digitalRead(bump_1)) {
    TURN_SCALAR = 0.40;
  }
  if (!digitalRead(bump_0)) {
    TURN_SCALAR = 0.00;
  }
}

void test_pd() {
  
  // variate_kp();
  // variate_kd();
  // variate_turn_scalar();

  
  drive_car(0, 1);
}

#endif
