#ifndef ROUTINES_H
#define ROUTINES_H

#include "pd_control.h"
#include "data_collection.h"
#include "cross.h"


// ROUTINES DESIGNED FOR NAVIGATING TRACK

void read_inner(uint16_t sensor_values[8]) {
  for (int i = 0; i < 8; i++) {
      if (i < 2 || i > 5) {
            sensor_values[i] = 0;
      }
  }
}

void drive_car(bool inner_sensors = 0, bool turn = 0) { // not a looping functions
  ECE3_read_IR(sensor_values);

  if (inner_sensors == 1) {
    read_inner(sensor_values); // this may or may not work, if sensor_values is not a global variable
  }
  
  int error = calc_error(sensor_values);
  
  store_error(error);
  store_cross(sensor_values);
  store_real_cross(sensor_values);
  store_sensors(sensor_values);

  /*
  uint16_t norm_values[8];
  calc_norm(sensor_values, norm_values);
  store_sensors(norm_values);
  */
  
  if ( turn ) { 
    pd_turn_control(error); // set wheels to turn either direction
  } else {
    pd_control(error); // wheels only go forward
  }

  // store_pwm(l_speed,r_speed); // must be after pd_control, stores pwm speeds
}


// LOOPING FUNCTIONS

void duration(int threshold, bool inner_sensors = 0, bool turn = 0){
  int ct = avg_encoder();
  threshold = threshold + ct;
  while (ct < threshold) {
    ct = avg_encoder();
    drive_car(inner_sensors, turn);
  }
}

#endif
