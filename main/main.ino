#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"

void setup() {
  initialize();

  K_P = 0.01;
  K_D = 0.2;
  
  duration(2000);
  stop_car();
  delay(500);
  output_data();
}

void loop() {
  //drive_car();
  
  // test_pd();
}

/* FUNCTIONS
 *  void drive_car()
 *  void stop_car()
 *  void duration(int encode_ct)
 *  
 */
