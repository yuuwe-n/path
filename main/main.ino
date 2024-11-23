#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"
#include "movement.h"

void setup() {
  initialize();

  //routine0();

/*
  K_P = 0.10;
  K_D = 0.35;
  
  duration(500);
  stop_car();
  delay(500);
  output_5();
  */
}

void routine0() {
  duration(500);
  donut(base_speed);
  duration(250);
}


void loop() {
  //drive_car();
  
  // test_pd();
}

/* FUNCTIONS
 *  void drive_car()
 *  void stop_car()
 *  void duration(int encode_ct)
 */
