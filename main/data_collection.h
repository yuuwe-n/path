#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "cross.h"

const int DATA_COUNT = 8000; // ~ the encoder count, maybe store every other data points

int count = 0;
int count_cross = 0;
int count_real_cross = 0;
int count_pwm = 0;
int count_sensors = 0;
int count_b = 0;

short error_arr[DATA_COUNT];
bool cross_arr[DATA_COUNT];
bool real_cross[DATA_COUNT];
byte block_arr[DATA_COUNT];

int8_t pwm[DATA_COUNT][2]; // arrays dont get allocated unless used in function
short sensors[DATA_COUNT][8];

void store_error(int error) {
  if (count < DATA_COUNT) {
    error_arr[count] = error;
  }
  count += 1;
}

void store_cross(bool cross) {
  if (count_cross < DATA_COUNT) {
    if (cross) {
        cross_arr[count_cross] = 1;
      } else {
        cross_arr[count_cross] = 0;
    }
  }
  count_cross +=1;
}

void store_real_cross(uint16_t sensor_values[8]) {
  if (count_real_cross < DATA_COUNT) {
    if (detect_real_cross(sensor_values)) {
        real_cross[count_real_cross] = 1;
    } else {
      real_cross[count_real_cross] = 0;
    }
  }
  count_real_cross += 1;
}

void store_block() {
  if (count_b < DATA_COUNT) {
    block_arr[count_b] = block_count;
  }
  count_b += 1;
}

// to change data => pwm array, we can save memory
void store_pwm(int l_speed, int r_speed) {
  if (count_pwm < DATA_COUNT) {


    if (pwm_dir[0]) {
      l_speed *= -1;
    }

    if (pwm_dir[1]) {
      r_speed *= -1;
    }
    
    pwm[count_pwm][0] = l_speed;
    pwm[count_pwm][1] = r_speed;
    count_pwm += 1;
  }
}


void store_sensors(uint16_t sensor_values[8]) {
  if (count_sensors < DATA_COUNT) {
    for (int i = 0; i < 8; i++) {
      sensors[count_sensors][i] = sensor_values[i];
    }
    count_sensors += 1;
  }
}

void output_error() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(error_arr[i]);
    Serial.print(",");
  }
  Serial.println();
}

void output_cross() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(cross_arr[i] * 1000);
    Serial.print(",");
  }
  Serial.println();
}

void output_real_cross() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(real_cross[i] * 2000);
    Serial.print(",");
  }
  Serial.println();
}

void output_block() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(block_arr[i] * 1000);
    Serial.print(",");
  }
  Serial.println();
}


void output_sensors() {
  for (int j = 0; j < 8; j++) {
      for (int i = 0; i < DATA_COUNT; i++) {
          Serial.print(sensors[i][j]);
          Serial.print(",");
      }
      Serial.println();
  }
  Serial.println();
}

void output_pwm() {
  for (int j = 0; j < 2; j++) {
      for (int i = 0; i < DATA_COUNT; i++) {
          Serial.print(pwm[i][j]);
          Serial.print(",");
      }
      Serial.println();
  }
  Serial.println();
}


void output_3() { // output error, cross piece, and real cross piece
  output_error();
  output_cross();
  output_real_cross();
}


void output_4() { // output errors, crosspiece, real crosspiece, sensors
  output_error();
  output_cross();
  output_real_cross();
  output_sensors();
}

void output_5() { // output errors, crosspiece, real crosspiece, sensors
  output_error();
  output_cross();
  output_real_cross();
  output_sensors();
  output_pwm();
}

void output() {
  while (true) {
    if (!digitalRead(bump_5)) {
      output_error();
      output_cross();
      //output_real_cross();
      output_block();
      output_pwm();
      // output_sensors();
    }
  }
}

#endif
