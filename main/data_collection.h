#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

const int DATA_COUNT = 2000; // ~ the encoder count, maybe store every other data points

int count = 0;
int count_pwm = 0;
int count_cross = 0;

/*
 * make data into a short
 * make cross piece into a bit or byte
 * 
 */

short data[DATA_COUNT];
bool cross[DATA_COUNT];
bool real_cross[DATA_COUNT];

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

int real_max = { 2500 , 1916 , 2344 , 1467 , 1727 , 2381 , 2130 , 2500 }

int consecutive_real_cross = 0;

bool detect_real_cross(uint16_t sensor_values[8]) {
  // Check if all sensor values are within 10% of real_max
  bool within_threshold = true;
  for (int i = 0; i < 8; i++) {
    int lower_bound = real_max[i] * 0.9; // 10% below real_max
    int upper_bound = real_max[i] * 1.1; // 10% above real_max
    if (sensor_values[i] < lower_bound || sensor_values[i] > upper_bound) {
      within_threshold = false;
      break;
    }
  }
  // Increment or reset consecutive detection counter
  if (within_threshold) {
    consecutive_real_cross += 1;
  } else {
    consecutive_real_cross = 0;
  }

  // Return true if detected two times in a row
  return consecutive_real_cross >= 2;
}

void store_error(int error, uint16_t sensor_values[8]) {
  if (count < DATA_COUNT) {
    data[count] = error;
    
    if (detect_crosspiece(sensor_values)) {
      cross[count] = 1;
      count_cross += 1;
    } else {
      cross[count] = 0;
      count_cross = 0;
    }
    // Set data[count][2] to 1500 only for consecutive crosspiece detections
    if (count_cross > 1) { // Trigger only on 2nd or higher consecutive detections
      real_cross[count] = 1;
    } else {
      real_cross[count] = 0; // Reset if not consecutive
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


short sensors[DATA_COUNT][8];
int count_sensors = 0;

void store_sensors(uint16_t sensor_values[8]) {
  if (count_sensors < DATA_COUNT) {
    for (int i = 0; i < 8; i++) {
      sensors[count_sensors][i] = sensor_values[i];
    }
    count_sensors += 1;
  }
}

/*
void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(cross[i]);
        Serial.print(",");
      }
    }
  }
}
*/

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
        Serial.print(data[i]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(cross[i]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(real_cross[i]);
        Serial.print(",");
      }
    }
  }
}

void output_5() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i]);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(cross[i]*1000);
        Serial.print(",");
      }
      Serial.println();
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(real_cross[i]*1500);
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
