#ifndef ROUTINES_H
#define ROUTINES_H

void variate_preset() {
  if (!digitalRead(bump_5)) {
    preset_0();
  }
  if (!digitalRead(bump_4)) {
    preset_0();
  }
  if (!digitalRead(bump_3)) {
    preset_0();
  }
  if (!digitalRead(bump_2)) {
    preset_0();
  }
  if (!digitalRead(bump_1)) {
    preset_0();
  }
  if (!digitalRead(bump_0)) {
    preset_0();
  }
}

void preset_0() {
  K_P = 0.01;
  K_D = 0.40;
}

#endif
