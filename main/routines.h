#ifndef ROUTINES_H
#define ROUTINES_H

#include "pd_control.h"

// ROUTINES DESIGNED FOR NAVIGATING TRACK

void drive_car() { // not a looping functions
  ECE3_read_IR(sensor_values);
  
  int error = calc_error(sensor_values);
  store_error(error,sensor_values); // STORES ERRORS & CROSS PIECE
  
  pd_control(error);
  store_pwm(l_speed,r_speed); // must be after pd_control, stores pwm speeds
}

// LOOPING FUNCTIONS

void duration(int encode_ct){ // looping function: drives car and stops after number of encoder counts
  while(true) {
    //Serial.println(avg_encoder());
    if (avg_encoder() >= encode_ct){
      stop_car();
      delay(500);
      output_all();
      return;
    }
    drive_car();
  }
}

#endif
