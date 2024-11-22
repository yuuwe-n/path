#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

const int DATA_COUNT = 500; // ~ the encoder count, maybe store every other data points

int count = 0;
int count_pwm = 0;
int count_cross = 0;

short data[DATA_COUNT][3];

// ADJUST CROSS_PIECE DETECTION THRESHOLD
bool detect_crosspiece(uint16_t sensor_values[8]) {
  // Check if all inner sensors (indices 2 to 5) are greater than 2400
  for (int i = 2; i <= 5; i++) {
    if (sensor_values[i] <= 2400) {
      return false;
    }
  }
  return true;
}

void store_error(int error, uint16_t sensor_values[8]) {
  if (count < DATA_COUNT) {
    data[count][0] = error;
    
    if (detect_crosspiece(sensor_values)) {
      data[count][1] = 1000;
      count_cross += 1;
    } else {
      data[count][1] = 0;
      count_cross = 0;
    }
    // Set data[count][2] to 1500 only for consecutive crosspiece detections
    if (count_cross > 1) { // Trigger only on 2nd or higher consecutive detections
      data[count][2] = 1500;
    } else {
      data[count][2] = 0; // Reset if not consecutive
    }
    count += 1;
  }
}

/*
// to change data => pwm array, we can save memory
byte pwm[DATA_COUNT][2];
void store_pwm(int l_speed, int r_speed) {
  if (count_pwm < DATA_COUNT) {
    pwm[count_pwm][0] = l_speed;
    pwm[count_pwm][1] = r_speed;
    count_pwm += 1;
  }
}
*/


uint16_t sensors[DATA_COUNT][8];
int count_sensors = 0;

void store_sensors(uint16_t sensor_values[8]) {
  if (count_sensors < DATA_COUNT) {
    for (int i = 0; i < 8; i++) {
      sensors[count_sensors][i] = sensor_values[i];
    }
    count_sensors += 1;
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
    }
  }
}

void output_sensors() {
  if (!digitalRead(bump_5)) {
    for (int j = 0; j < 8; j++) {
      for (int i = 0; i < DATA_COUNT; i++) {
          Serial.print(sensors[i][j]);
          Serial.print(",");
      }
      Serial.println();
    }
  }
}

void output_3() { // output error, cross piece, and real cross piece
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

void output_5() {
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
      Serial.println();
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < DATA_COUNT; i++) {
            Serial.print(sensors[i][j]);
            Serial.print(",");
        }
        Serial.println();
      }
    }
  }
}

/*
void output_all() { // output, cross piece, real cross piece, pwm values
  while (true){
    if (!digitalRead(bump_5)) {
      for (int j = 0; j < 3; j++) {
        for (int i = 0; i < DATA_COUNT; i++) {
            Serial.print(data[i][j]);
            Serial.print(",");
        }
        Serial.println();
      }
      for (int j = 0; j < 2; j++) {
        for (int i = 0; i < DATA_COUNT; i++) {
            Serial.print(pwm[i][j]);
            Serial.print(",");
        }
        Serial.println();
      }
    }
  }
}
*/

#endif
