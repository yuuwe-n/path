#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();
  
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.50;
  TURN_SCALAR = 0.15; // this is the best i could find ( range from 0.10 - > max 0.30 ,,, 0.15 seems best)

  // routine_0();
}

void routine_0() {

  bool cross1_flag = false;
  bool turnaround_flag = false;
  bool end_flag = false;

  while(true) {
  
    drive_car(0, 1);


  
    if (block_count == 1 && !cross1_flag) {
      cross1_flag = true;
      move_forward(100, base_speed); // 100 encoder cts @ base speed
    }
    
    if (block_count == 2 && !turnaround_flag) { 
      turnaround_flag = true; 
      half_donut(base_speed);
    }

/*
    if (block_count == 4 && !end_flag) { 
      end_flag = true;      
      stop_car();
      delay(500);
      output();
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
  
  test_pd();
}

/* FUNCTIONS
 *  void drive_car(0, turn = 1);
 *  void stop_car()
 *  void duration(int encode_ct)
 */
