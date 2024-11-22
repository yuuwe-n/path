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
    K_D = 1;
  }
  if (!digitalRead(bump_4)) {
    K_D = 0.8;
  }
  if (!digitalRead(bump_3)) {
    K_D = 0.6;
  }
  if (!digitalRead(bump_2)) {
    K_D = 0.4;
  }
  if (!digitalRead(bump_1)) {
    K_D = 0.2;
  }
  if (!digitalRead(bump_0)) {
    K_D = 0.1;
  }
}

void variate_kp() {
  if (!digitalRead(bump_5)) {
    K_P = 0.25;
  }
  if (!digitalRead(bump_4)) {
    K_P = 0.20;
  }
  if (!digitalRead(bump_3)) {
    K_P = 0.15;
  }
  if (!digitalRead(bump_2)) {
    K_P = 0.10;
  }
  if (!digitalRead(bump_1)) {
    K_P = 0.05;
  }
  if (!digitalRead(bump_0)) {
    K_P = 0.01;
  }
}

void test_pd() {
  //K_P = 0.01;
  K_D = 0.4;
  variate_kp();
  drive_car();
  //Serial.println(K_P);
}

// { K_P, K_D }
float presets[3][2] = { 
{0, 0} ,
{0.2, 0.4} ,
{0.25, 0.4}
};

void test_presets() {
  K_P = presets[0][0]; // row, column
  K_D = presets[0][1];
  variate_kp();
  drive_car();
}

#endif
