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

  // calculate error values
  int error = calc_error(sensor_values);

  // calculate norm values
  uint16_t norm_values[8];
  calc_norm(sensor_values, norm_values);
  
  // detect consecutive cross values from norm_values
  bool cross = detect_cross(norm_values);
  track_block(cross);

  // detect non consecutive 
  bool c = detect_c(norm_values); // detect inner 4 sensors are 1000
  // bool c2 = detect_cross_2(norm_values);
  
  
  if ( turn ) { 
    pd_turn_control(error); // set wheels to turn either direction
  } else {
    pd_control(error); // wheels only go forward
  }
  
  //store_encoder(avg_encoder());
  store_error(error); 
  // store_data(norm_values);
  // store_data(sensor_values);
  store_block();
  store_cross(c);

  // store_pwm(l_speed,r_speed); // must be after pd_control, stores pwm speeds
}


// LOOPING FUNCTIONS

void duration(int threshold, bool inner_sensors = 0, bool turn = 1){
  int ct = avg_encoder();
  threshold = threshold + ct;
  while (ct < threshold) {
    ct = avg_encoder();
    drive_car(inner_sensors, turn);
  }
}

#endif
