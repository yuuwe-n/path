#include <ECE3.h>
#include "init.h"
#include "encoder.h"
#include "motor_control.h"
#include "pd_control.h"
#include "tests.h"

void setup() {
  initialize();

  // test_direction(); // TEST THIS FIRST THING TMMRW
  
  // duration(2000); // 2000 encoder counts

}

void loop() {
  //drive_car();
  test_pd();
}
