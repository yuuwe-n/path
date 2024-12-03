#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "cross.h"

// note: arrays/variables do not get allocated unless they are run in main file

const int DATA_COUNT = 9000;
// max data count should be above 8200 for a full track run

int count = 0;
int count_encoder = 0;
int count_cross = 0;
int count_pwm = 0;
int count_data = 0;
int count_block = 0;

short encoder_arr[DATA_COUNT];

short error_arr[DATA_COUNT];

bool cross_arr[DATA_COUNT];
byte block_arr[DATA_COUNT];

int8_t pwm[DATA_COUNT][2]; 
short data[DATA_COUNT][8];

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


void store_encoder(int encoder) {
  if (count_encoder < DATA_COUNT) {
    encoder_arr[count_encoder] = avg_encoder();
  }
  count_encoder += 1;
}

void store_block() {
  if (count_block < DATA_COUNT) {
    block_arr[count_block] = block_count;
  }
  count_block += 1;
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


void store_data(uint16_t sensor_values[8]) {
  if (count_data < DATA_COUNT) {
    for (int i = 0; i < 8; i++) {
      data[count_data][i] = sensor_values[i];
    }
    count_data += 1;
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

void output_block() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(block_arr[i] * 1000);
    Serial.print(",");
  }
  Serial.println();
}

void output_data() {
  for (int j = 0; j < 8; j++) {
      for (int i = 0; i < DATA_COUNT; i++) {
          Serial.print(data[i][j]);
          Serial.print(",");
      }
      Serial.println();
  }
  Serial.println();
}

void output_encoder() {
  for (int i = 0; i < DATA_COUNT; i++) {
    Serial.print(encoder_arr[i]);
    Serial.print(",");
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


void output() {
  while (true) {
    if (!digitalRead(bump_5)) {
      output_encoder();

      output_error();
      // output_cross();
      output_block();
      
      // output_pwm();
      //output_data();
    }
  }
}

#endif
