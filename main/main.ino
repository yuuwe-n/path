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
  
  duration(500); // 2000 encoder counts

}

void loop() {
  //drive_car();
  
  // test_pd();

  //test_direction();
}

/* FUNCTIONS
 *  void drive_car()
 *  void stop_car()
 *  void duration(int encode_ct)
 *  
 */
