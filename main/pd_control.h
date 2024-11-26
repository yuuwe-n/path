#ifndef PD_CONTROL_H
#define PD_CONTROL_H

#include "error.h"

int calc_p(int error) {
  int p = K_P * abs(error);
  return p;
}

int calc_d(int error, int prev_error) {
  int d = K_D *  (prev_error - error); //error - prev_error
  return d;
}

void pd_control(int error) {
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   int p = calc_p(error);
   int d = calc_d(error, prev_error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p + d; // Speed up left wheel
      r_speed = base_speed - p - d; // Slow down right wheel
                      
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p - d; // Slow down left wheel
      r_speed = base_speed + p + d; // Speed up right wheel
    }

    l_speed = constrain(l_speed, 0 , max_speed);
    r_speed = constrain(r_speed, 0, max_speed);
  
    analogWrite(left_pwm_pin, l_speed);
    analogWrite(right_pwm_pin, r_speed);

    prev_error = error;
}

bool pwm_dir[2] = {0, 0}; // allows to collect data magnitude and direction of pwm

void pd_turn_control(int error) {
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   int p = calc_p(error);
   int d = calc_d(error, prev_error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p + d; // Speed up left wheel
      r_speed = base_speed - p - d; // Slow down right wheel
                      
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p - d; // Slow down left wheel
      r_speed = base_speed + p + d; // Speed up right wheel
    }

    if (l_speed < 0) {
      l_speed = abs(l_speed) * TURN_SCALAR;
      digitalWrite(left_dir_pin, HIGH); // backward
      pwm_dir[0] = 1;
    } else {
      digitalWrite(left_dir_pin, LOW);  // forward
      pwm_dir[0] = 0;
    }
    if (r_speed < 0) {
        r_speed = abs(r_speed) * TURN_SCALAR;
        digitalWrite(right_dir_pin, HIGH); // backward
        pwm_dir[1] = 1;
    } else {
        digitalWrite(right_dir_pin, LOW);  // forward
        pwm_dir[1] = 0;
    }

    l_speed = constrain(l_speed, 0 , max_speed);
    r_speed = constrain(r_speed, 0, max_speed);
  
    analogWrite(left_pwm_pin, l_speed);
    analogWrite(right_pwm_pin, r_speed);

    prev_error = error;
}

#endif
