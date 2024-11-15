#ifndef PD_CONTROL_H
#define PD_CONTROL_H

// START HERE AND TEST YOUR STORE_DATA FUNCTION

const int DATA_COUNT = 1500;
int count = 0;
short data[DATA_COUNT];

void store_data(int error) {
  if (count < DATA_COUNT) {
    data[count] = error;
    count += 1;
  }
}

void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.println(data[i]);
        delay(20);
      }
    }
    //digitalWrite(LED_RF, HIGH);
  }
}

int calc_error(uint16_t input[8]) {

/*
 * Negative error : black line is to the left => ERROR = -40mm => error < 0 : steer to the left
 * Positive error : black line is to the right => ERROR = 40mm => error > 0 : steer to the right
 */
  
  int error;
  int weighted_sum = 0;
  int temp[8]={0,0,0,0,0,0,0,0};
  
  for (int i = 0; i < 8; i++) {
    temp[i] = input[i] - mins[i];
    if (temp[i] <=0) {
      temp[i]=0;
    } 
    temp[i] = temp[i] * 1000 / maxs[i];
    weighted_sum += temp[i] * weights[i];
  }
  error = weighted_sum / 8;
  
  return error;
}

int calc_p(int error) {
  int p = K_P * abs(error);
  return p;
}

int calc_d(int error, int prev_error) {
  int d = K_D * abs(error - prev_error);
  return d;
}

int* control_car(int error, int prev_error = 0) { // adjusts every loop, does not rely on loop
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   static int pwm[2]; // [0] is left_pwm, [1] is right_pwm

   int p = calc_p(error);
   int d = calc_d(error, prev_error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p; // Speed up left wheel
      r_speed = base_speed - p; // Slow down right wheel                  
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p; // Slow down left wheel
      r_speed = base_speed + p; // Speed up right wheel
    }

   prev_error = error;

  //l_speed = constrain(l_speed, 0, max_speed);
  //r_speed = constrain(r_speed, 0, max_speed);
  
  analogWrite(left_pwm_pin, l_speed);
  analogWrite(right_pwm_pin, r_speed);

  // return pwm speeds
  pwm[0] = l_speed;
  pwm[1] = r_speed;
  return pwm;
}

void drive_car() { // is not a loop
  set_forward();
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);
  store_data(error);
  control_car(error);
}

void stop_car() { // stop car
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
  digitalWrite(LED_RF, HIGH); // turn on yellow LED 
}

void duration(int max_revs){ // looping function: drives car and stops after number of revolutions
  while(true) {
    //Serial.println(avg_encoder());
    if (revs() >= max_revs){
      stop_car();
      delay(500);
      output_data();
      return;
    }
    drive_car();
  }
}
#endif
