#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

int ct_crosspiece = 0;

bool detect_crosspiece(uint16_t sensor_values[8]) {
  for (int i = 2; i <= 5; i++) {
    if (sensor_values[i] >= 2450) {
      ct_crosspiece +=1 ;
    } else {
      ct_crosspiece = 0;
    }
  }

  if (ct_crosspiece >= 3) {
    return true;
  } else {
    return false;
  }
}

const int DATA_COUNT = 2000; // ~ the encoder count, maybe store every other data points
int count = 0;
int count_pwm = 0;
//short data[DATA_COUNT][2];

short data[DATA_COUNT][3];

void store_error(int error, uint16_t sensor_values[8]) {
  if (count < DATA_COUNT) {
    data[count][0] = error;
    for (int i = 2; i < 6; i++) {
        if (sensor_values[i] >= 2450) {
            data[count][1] = 1000;
        } else {
          data[count][1] = 0;
        }
    }
    if (detect_crosspiece(sensor_values)) {
      data[count][3] = 1500;
    }
    count += 1;
  }
}

// to change data => pwm array, we can save memory
byte pwm[DATA_COUNT][2];
void store_pwm(int l_speed, int r_speed) {
  if (count_pwm < DATA_COUNT) {
    pwm[count_pwm][0] = l_speed;
    pwm[count_pwm][1] = r_speed;
    count_pwm += 1;
  }
}

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
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i][2]);
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
