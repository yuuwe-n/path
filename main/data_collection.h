#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

const int DATA_COUNT = 1000;
int count = 0;
int count_pwm = 0;
short data[DATA_COUNT][2];

void store_error(int error, uint16_t sensor_values[8]) {
  if (count < DATA_COUNT) {
    data[count][0] = error;
    for (int i = 2; i < 6; i++) {
        if (sensor_values[i] >= 2400) {
            data[count][1] = 1000;
        } else {
          data[count][1] = 0;
        }
    }
    count += 1;
  }
}

byte pwm[DATA_COUNT][2];

void store_pwm(int l_speed, int r_speed) {
  if (count_pwm < DATA_COUNT) {
    pwm[count_pwm][0] = l_speed;
    pwm[count_pwm][1] = r_speed;
    count_pwm += 1;
  }
}

// we can try using this array later, but to save memory keep it commented
// remember if we uncomment, to change data => pwm array
/*
void store_pwm(int l_speed, int r_speed) {
  if (count < DATA_COUNT) {
    data[count][0] = l_speed;
    data[count][1] = r_speed;
    count += 1;
  }
}
*/

void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i][0]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i][1]);
        Serial.print(",");
      }
    }
  }
}


void output_all() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i][0]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i][1]);
        Serial.print(",");
      }
    }
    if (!digitalRead(bump_0)) {
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(pwm[i][0]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(pwm[i][1]);
        Serial.print(",");
      }
    }
  }
}


#endif
