#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();

  
  base_speed = 30;
  K_P = 0.070;
  K_D = 0.50;
  
  TURN_SCALAR = 0.45;

  // routine_test_pd();
  //routine_drive_car();
  //routine_0();
  //routine_test();

  routine_1();
}

void routine_1() {
  
  bool cross1_flag = false;
  bool cross2_flag = false;
  bool cross3_flag = false;
  bool cross4_flag = false;
  
  while(true) {
    

    
    drive_car(0, 1);

    if (block_count == 1 && !cross1_flag) {
      cross1_flag = true;
      
      stop_start(2000);
    }

    if (block_count == 2 && !cross2_flag) {
      cross2_flag = true;
      
      stop_start(2000);
    }

    if (block_count == 3 && !cross3_flag) {
      cross3_flag = true;
      
      stop_start(2000);
    }

    if (block_count == 4 && !cross4_flag) {
      cross4_flag = true;
      
      stop_start(2000);
    }

    if (!digitalRead(bump_5)) {
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

void routine_0() {

  int total_encoder_ct = avg_encoder();
  bool cross1_flag = false;
  bool turnaround_flag = false;
  bool end_flag = false;

  while(true) {
  
    drive_car(0, 1);
    total_encoder_ct = avg_encoder();

    if (block_count == 1 && !cross1_flag) { // WORK ON THIS FUNCTION to do loop consistently
      cross1_flag = true;
      move_forward(90, base_speed); // 100 encoder cts @ base speed
      duration(600); // original 720 -> 620 -> 600
      move_forward(90,base_speed);
    }

    // false turnaround // maybe do >= 2 , so it turn around eventually
    if (block_count == 2 && !turnaround_flag && total_encoder_ct >= 3500) { 
      turnaround_flag = true; 
      half_donut(base_speed);
    }

    if (block_count >= 4 && !end_flag && total_encoder_ct >= 7000) { 
      end_flag = true; 
      stop_car();
      delay(500);
      
      output();
    }

    if (total_encoder_ct >= 17000) { 
      stop_car();
      delay(500);
      
      output();
    }
    
    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);
      
      output();
    }
  }
}

void routine_test() {
  while(true) {
    bool cross1_flag = false;
    bool cross2_flag = false;
    
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

void routine_test_pd() {
  while(true) {
    test_pd();
  }
}

void loop() {
}
