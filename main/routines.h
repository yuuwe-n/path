#ifndef ROUTINES_H
#define ROUTINES_H

#include "pd_control.h"
#include "data_collection.h"

// ROUTINES DESIGNED FOR NAVIGATING TRACK

void read_inner(uint16_t sensor_values[8]) {
  for (int i = 0; i < 8; i++) {
      if (i < 2 || i > 5) {
            sensor_values[i] = 0;
      }
  }
}

void drive_car(bool inner_sensors = 0) { // not a looping functions
  ECE3_read_IR(sensor_values);

  if (inner_sensors == 1) {
    read_inner(sensor_values); // this may or may not work, if sensor_values is not a global variable
  }
  
  int error = calc_error(sensor_values);
  store_error(error,sensor_values); // STORES ERRORS & CROSS PIECE
  
  pd_control(error);
  store_pwm(l_speed,r_speed); // must be after pd_control, stores pwm speeds
}



// LOOPING FUNCTIONS

void duration(int threshold){
  int ct = avg_encoder();
  threshold = threshold + ct;
  while (ct < threshold) {
    ct = avg_encoder();
    drive_car();
  }
}

#endif
