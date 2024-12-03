#ifndef ROUTINES_H
#define ROUTINES_H

#include "pd_control.h"
#include "data_collection.h"
#include "cross.h"
#include "movement.h"


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
  
  store_encoder(avg_encoder());
  store_error(error); 
  // store_data(norm_values);
  // store_data(sensor_values);
  store_block();
  //store_cross(c);

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

// drives car without recording any data
void auto_drive_car(bool inner_sensors = 0, bool turn = 0) { 
  ECE3_read_IR(sensor_values);

  if (inner_sensors == 1) {
    read_inner(sensor_values);
  }

  // calculate error values
  int error = calc_error(sensor_values);
  
  if ( turn ) { 
    pd_turn_control(error); // set wheels to turn either direction
  } else {
    pd_control(error); // wheels only go forward
  }
}

// drives car for duration without recording any data
void auto_duration(int threshold, bool inner_sensors = 0, bool turn = 1){ 
  int ct = avg_encoder();
  threshold = threshold + ct;
  while (ct < threshold) {
    ct = avg_encoder();
    drive_car(inner_sensors, turn);
  }
}


// ROUTINES

void routine_test() {
  bool cross1_flag = false;
  bool cross2_flag = false;
  while(true) {
    
    drive_car(0, 1);

    if (block_count == 1 && !cross1_flag) {
      cross1_flag = true;
      
      stop_car();
      delay(500);
      
      output();
      //move_forward(90, base_speed); // 100 encoder cts @ base speed
    }

    /*
    if (block_count == 2 && !turnaround_flag && total_encoder_ct >= 3500) { 
      cross2_flag = true; 
      half_donut(base_speed);
    }
    */
    
    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);
      
      output();
    }
  }
}

void routine_1() { // before turn around -> end

  int total_encoder_ct = avg_encoder();

  bool turnaround_flag = false;
  bool cross1_turnaround_flag = false;
  bool end_flag = false;
  int encoder_at_turnaround = 0;
  
  while(true){

    drive_car(0, 1);
    total_encoder_ct = avg_encoder();
  
    if (block_count == 1 && !turnaround_flag) { 
        turnaround_flag = true; 
        half_donut(base_speed);
        
        encoder_at_turnaround = avg_encoder();
      }
  
      if ( ( total_encoder_ct >= (5460 + encoder_at_turnaround )) && !cross1_turnaround_flag && turnaround_flag) {
          cross1_turnaround_flag = true;
          
          move_forward(90, base_speed);
          duration(700);
          move_forward(90,base_speed);
      }
  
      if (block_count >= 3 && !end_flag) { 
        end_flag = true;
        stop_car();
        delay(500);
        
        output();
      }
  }
}

void routine_drive_car() {
  while(true) {
    drive_car(0,1);
    
    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);
      output();
    }
  }
}

void routine_stop_start() {
  int last_block_count = 0; // Keep track of the last processed block count
  
  while (true) {
    drive_car(0, 1);

    // Check if block_count has increased
    if (block_count > last_block_count) {
      last_block_count = block_count; // Update the last block count
      
      // Stop and start for every new block count
      stop_start(2000); // Adjust the delay as needed
    }

    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);
      output();
    }
  }
}


#endif
