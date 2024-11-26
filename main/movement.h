#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "encoder.h"
#include "motor_control.h"

/*
 * FILE FOR CONTROLLING HARD WIRED CAR MOVEMENTS
 */

int encoder_counts = 0;
int final_count = 0;

// may need to add a delay before and after, or use stop_car

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

void donut(int spd, bool dir = true) {
  rotate(728, spd, dir); // test how many encoder counts is one revolution
}

void half_donut(int spd, bool dir = true) {
  rotate(364, spd, dir); // test how many encoder counts is one revolution
}

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

void loop_1(int threshold, int spd, bool dir = 1) { // threshold (in encoder counts)

  int ct = avg_encoder();
  threshold = threshold + ct; // doesn't matter if encoder is reset or not
  while (ct < threshold) {
        if (dir == true) { // spin right
          analogWrite(left_pwm_pin, spd);
          analogWrite(right_pwm_pin, 0);
        } else { // spin left
          analogWrite(left_pwm_pin, 0);
          analogWrite(right_pwm_pin, spd);
        }
      ct = avg_encoder();
  }
  
  analogWrite(left_pwm_pin, spd);
  analogWrite(right_pwm_pin, spd);
  set_forward();
}


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

#endif
