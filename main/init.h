#ifndef INIT_H
#define INIT_H

#include <Arduino.h>

uint16_t sensor_values[8]; // sensor values: right -> left, 0 -> 7

const int left_nslp_pin=31;
const int left_dir_pin=29;
const int left_pwm_pin=40;

const int right_nslp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;

const int bump_0 = 24; // this bump is on the right most side
const int bump_5 = 28; // bump is on left most side
// TRUE => bump is not switched
// FALSE => bump is switched

const int LED_Y = 41;
const int LED_B = 77;

// pwm signal ranges from: 0 - 255 
int max_speed = 127;
int base_speed = 40;

int l_speed = base_speed;
int r_speed = base_speed;

int prev_error = 0;

int weights[8] = {-15, -14, -12, -8, 8, 12, 14, 15};
int mins[8] = {756, 595,686,503,572,663,641,706};
int maxs[8] = {1744,1321,1658,964,1155,1718,1489,1794};

float K_P = 0.01;
float K_D = 0.5;

void initialize() {
  ECE3_Init();
  
  Serial.begin(9600);
  pinMode(bump_5,INPUT_PULLUP);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_B, OUTPUT);

  
  pinMode(left_nslp_pin,OUTPUT);
  pinMode(left_dir_pin,OUTPUT);
  pinMode(left_pwm_pin,OUTPUT);

  pinMode(right_nslp_pin,OUTPUT);
  pinMode(right_dir_pin,OUTPUT);
  pinMode(right_pwm_pin,OUTPUT);

  digitalWrite(left_dir_pin,LOW);
  digitalWrite(left_nslp_pin,HIGH);
  
  digitalWrite(right_dir_pin,LOW);
  digitalWrite(right_nslp_pin,HIGH);

  resetEncoderCount_left();
  resetEncoderCount_right();

  delay(4000); // wait for setup
}

#endif
