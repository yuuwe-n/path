#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "encoder.h"
#include "motor_control.h"

/*
 * FILE FOR CONTROLLING HARD WIRED CAR MOVEMENTS
 */

// rotate for N encoder counts
void rotate(int threshold, int spd, bool dir) { // threshold (in encoder counts)
  if (dir == true) { // spin right
    set_right();
  } else { // spin left
    set_left();
  }

  int ct = avg_encoder();
  threshold = threshold + ct; // doesn't matter if encoder is reset or not
  while (ct < threshold) {
      analogWrite(left_pwm_pin, spd);
      analogWrite(right_pwm_pin, spd);
      ct = avg_encoder();
  }
  set_forward();
}

// spin 360 degrees
void donut(int spd, bool dir = true) {
  rotate(728, spd, dir); // test how many encoder counts is one revolution
}

// spin 180 degrees
void half_donut(int spd, bool dir = true) {
  rotate(364, spd, dir); // test how many encoder counts is one revolution
}

// move car forwad for n encoder counts
void move_forward(int threshold, int spd) {
  int ct = avg_encoder();
  threshold = threshold + ct;
  while (ct < threshold) {
    set_forward();
    ct = avg_encoder();
    analogWrite(left_pwm_pin, spd);
    analogWrite(right_pwm_pin, spd);
  }
}

#endif
