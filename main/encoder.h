#ifndef ENCODER_H
#define ENCODER_H

#include "motor_control.h"

int avg_encoder() {
  int l_encoder = getEncoderCount_left();
  int r_encoder = getEncoderCount_right();
  return ((l_encoder + r_encoder) / 2.0);
}

void reset_encoder() {
  resetEncoderCount_left();
  resetEncoderCount_right();
}

int revs() { // returns wheel revolutions
  int revolutions = avg_encoder() / 360;
  return revolutions;
}

void test_encoder() {
  set_nlsp(true);
  analogWrite(left_pwm_pin, 40);
  analogWrite(right_pwm_pin, 40);
  Serial.print(avg_encoder());
  Serial.print('\t');
  Serial.print(revs());
  Serial.println();
}

#endif
