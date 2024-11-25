#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();
  /*
  base_speed = 40; // when speed is very low, k_p and k_d dominate
  K_P = 0.12;
  K_D = 0.30;
  TURN_SCALAR = 0.20;

  duration(3000, 0 , 1);
  
  stop_start(2000);
  */

/*
  duration(500, 0, 0);

  stop_start(2000);

  duration(600,0,1);

  stop_start(2000);

  duration(500,0,0);

  stop_start(2000);
  */
  
  base_speed = 40;
  K_P = 0.12;
  //K_D = 0.50;
  K_D = 0.60;
  TURN_SCALAR = 0.25;
  // TURN_SCALAR = 0.20;
  
  // void drive_car(bool inner_sensors = 0, bool turn = 0)

  // void drive_car(1, 1) , does not work for loops, loops rely on outter sensors

  bool loop1_flag = false;
  bool turnaround_flag = false; // track_block == 3

  while(true) {
    drive_car(0, 1);

/*
    if (block_count == 1 && !loop1_flag) {
      loop1_flag = true;
      set_forward();
      analogWrite(left_pwm_pin, 40);
      analogWrite(right_pwm_pin, 40);
      delay(300);
      stop_start(1000);
    }
    */

    if (block_count == 1 && !turnaround_flag) { 
      // Only execute if track_block == 3 and the flag is false
      turnaround_flag = true; // Set the flag to true to prevent re-execution
      half_donut(base_speed); // Replace with your desired function
    }
    
    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);
      
      output();
    }
  }
}

  /*
  stop_car();
  delay(500);
  output_5();
  */


void loop() {
  //drive_car();
  
  //test_pd();
}

/* FUNCTIONS
 *  void drive_car()
 *  void stop_car()
 *  void duration(int encode_ct)
 */
