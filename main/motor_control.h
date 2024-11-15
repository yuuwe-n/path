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

void set_right() { // CHECK THESE PINS
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(right_dir_pin,HIGH);
}

void set_left() {
  digitalWrite(left_dir_pin,HIGH);
  digitalWrite(right_dir_pin,LOW);
}

void test_direction(){
  set_nlsp(true);
  set_left();
  analogWrite(left_pwm_pin, 25);
  analogWrite(right_pwm_pin, 25);
}

#endif
