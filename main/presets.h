#ifndef ROUTINES_H
#define ROUTINES_H

void variate_preset() {
  if (!digitalRead(bump_5)) {
    preset_0();
  }
  if (!digitalRead(bump_4)) {
    preset_1();
  }
  if (!digitalRead(bump_3)) {
    preset_2();
  }
  if (!digitalRead(bump_2)) {
    preset_3();
  }
  if (!digitalRead(bump_1)) {
    preset_4();
  }
  if (!digitalRead(bump_0)) {
    preset_5();
  }
}

void preset_0() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.20;
  TURN_SCALAR = 0.15;
}

void preset_1() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.30;
  TURN_SCALAR = 0.15;
}

void preset_2() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.40;
  TURN_SCALAR = 0.15;
}

void preset_3() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.50;
  TURN_SCALAR = 0.15;
}

void preset_4() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.60;
  TURN_SCALAR = 0.15;
}

void preset_5() {
  base_speed = 40;
  K_P = 0.15;
  K_D = 0.70;
  TURN_SCALAR = 0.15;
}

#endif
