#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();

  //routine_0();

  K_P = 0.10;
  // K_D = 0.30 // holy good
  K_D = 0.30; 


  // void drive_car(bool inner_sensors = 0, bool turn = 0)

  // void drive_car(1, 1) , does not work for loops, loops rely on outter sensors

  TURN_SCALAR = 0.20;

  while(true) {
    drive_car(0, 1);
    
    
    if (!digitalRead(bump_5)) {
      stop_car();
      delay(500);

      
      output();
      
      /*
      while (true) {
        if (!digitalRead(bump_5)) {
          Serial.println(block_count);
        }
      }
      */
    }
  }
}


void routine_0() {

  // duration(int threshold, bool inner_sensors = 0, bool turn = 0)
  // donut(base_speed); 
  // loop_1 ( int threshold, int spd, bool dir); 

  K_P = 0.10;
  K_D = 0.35;
  
  duration(550, 0 , 0);
  stop_start(2000);
  loop_1(500, base_speed, 1);
  stop_start(2000);

  base_speed = 20;
  duration(500, 1, 0);
  stop_start(2000);
  base_speed = 40;

}

  /*
  stop_car();
  delay(500);
  output_5();
  */


void loop() {
  //drive_car();
  
  test_pd();
}

/* FUNCTIONS
 *  void drive_car()
 *  void stop_car()
 *  void duration(int encode_ct)
 */
