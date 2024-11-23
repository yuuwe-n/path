#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

/*
 * FILE FOR CONTROLLING MOTOR DIRECTION, NLSP, MOTOR PINS
 */

void set_nlsp(bool wheels) {
  // true => turn on wheels
  // false => turn off wheels
  digitalWrite(left_nslp_pin, wheels);
  digitalWrite(right_nslp_pin, wheels);
}

void set_forward() {
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(right_dir_pin,LOW);
}

void set_right() {
  digitalWrite(left_dir_pin,LOW); // forward
  digitalWrite(right_dir_pin,HIGH); // backward
}

void set_left() {
  digitalWrite(left_dir_pin,HIGH); // backward
  digitalWrite(right_dir_pin,LOW); // forward
}

void stop_car() { // stop car
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
  digitalWrite(LED_Y, HIGH); // turn on yellow LED 
}

void start_car() { // start car
  analogWrite(left_pwm_pin, 1);
  analogWrite(right_pwm_pin, 1);
  digitalWrite(LED_Y, LOW); // turn on yellow LED
}

void stop_start(int t) {
  stop_car();
  delay(t);
  start_car();
}

void test_direction(){
  set_nlsp(true);
  set_right();
  analogWrite(left_pwm_pin, 40);
  analogWrite(right_pwm_pin, 40);
}

#endif
