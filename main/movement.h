#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "encoder.h"
#include "motor_control.h"

/*
 * FILE FOR CONTROLLING HARD WIRED CAR MOVEMENTS
 */

void donut(); // 360 degree
void half_donut(); // 180 degree

void donut(bool dir) {
  rotate(dir, 360); // test how many encoder counts is one revolution
}

void half_donut(bool dir) {
  rotate(dir, 360); // test how many encoder counts is one revolution
}

// diameter of wheel is 7cm
// measure how many encoder counts is one circle
// divide encoder counts by distance (cm) => encoder counts per cm
// set speed to be really slow, and measure 
int encoder_counts = 0;
int final_count = 0;

void test_rotation() {
  resetEncoderCount_left();
  resetEncoderCount_right();
  
  analogWrite(left_pwm_pin, 25);
  analogWrite(right_pwm_pin, 25);
  
  delay(2000);
  while(true) {
    encoder_counts = avg_encoder();
    if (!digitalRead(bump_5)){
      analogWrite(LED_Y, HIGH);
      break;
    }
  }
  final_count = encoder_counts;

  while(true) {
    Serial.println(final_count);
  }

  delay(2000);
}

// may need to add a delay before and after, or use stop_car
void rotate(bool dir, int threshold) { // threshold (in encoder counts)
  if (dir == true) { // spin right
    set_right();
  } else { // spin left
    set_left();
  }

  int ct = avg_encoder();
  threshold = threshold + ct; // doesn't matter if encoder is reset or not
  while (ct < threshold) {
      analogWrite(left_pwm_pin, 40);
      analogWrite(right_pwm_pin, 40);
  }
}

#endif
