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

  routine_0();  
}

void routine_0() {

  int total_encoder_ct = avg_encoder();
  bool cross1_flag = false;
  bool turnaround_flag = false;
  
  bool cross1_turnaround_flag = false;
  bool end_flag = false;

  int encoder_at_turnaround = 0;

  auto_duration(400); // doesn't record any data, just calibrates the car without false detecting crosspieces

  while(true) {  
    
    drive_car(0, 1);
    total_encoder_ct = avg_encoder();

     // FIRST LOOP
    if (block_count == 1 && !cross1_flag) {
      cross1_flag = true;
      move_forward(90, base_speed);
      duration(600);
      move_forward(90,base_speed);
    }

    // TURNAROUND
    if (block_count == 2 && !turnaround_flag && total_encoder_ct >= 3500) { 
      turnaround_flag = true; 
      half_donut(base_speed);
      
      encoder_at_turnaround = avg_encoder();
    }

    // LOOP TURNAROUND
    if ( ( total_encoder_ct >= (5460 + encoder_at_turnaround )) && !cross1_turnaround_flag && turnaround_flag) {
        cross1_turnaround_flag = true;
        
        move_forward(90, base_speed);
        duration(700);
        move_forward(90,base_speed);
    }

    // END OF TRACK
    if (block_count >= 4 && !end_flag && total_encoder_ct >= 13000) { //adjust this encoder ct
      end_flag = true; 
      stop_car();
      delay(500);
      
      output();
    }

    // BACKUP END RUN
    if (block_count >= 5 || total_encoder_ct >= 14000) {  // adjust this encoder ct
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

void loop() {
}
