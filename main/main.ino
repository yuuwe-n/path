#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();

  // lower k_p , raise k_d
  
  base_speed = 30;
  K_P = 0.14; // 0.12 -> 0.14
  K_D = 1.2; // 0.60 // 1.20 good // 1.80 fail, but also good
  
  TURN_SCALAR = 0.15; // this is the best i could find ( range from 0.10 - > max 0.30 ,,, 0.15 seems best)
  // 0.20 slows down too much, when K_d is so high

  routine_0();
  //routine_test();
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


void loop() {
  //drive_car();
  
  //test_pd();
}

/* FUNCTIONS
 *  void drive_car(0, turn = 1);
 *  void stop_car()
 *  void duration(int encode_ct)
 */
