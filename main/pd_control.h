#ifndef PD_CONTROL_H
#define PD_CONTROL_H

const int DATA_COUNT = 500;
int count = 0;
short data[DATA_COUNT][2];

void store_data(int error, uint16_t sensor_values[8]) {
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


short pwm[DATA_COUNT][2];

void store_pwm(int l_speed, int r_speed) {
  if (count < DATA_COUNT) {
    data[count][0] = l_speed;
    data[count][1] = r_speed;
    count += 1;
  }
}


void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.println(data[i][0]);
        delay(20);
      }
      Serial.println("-----------------");
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.println(data[i][1]);
        delay(20);
      }
    }
    //digitalWrite(LED_Y, HIGH);
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
  int d = K_D *  (error - prev_error);
  return d;
}

int* control_car(int error) { // adjusts every loop, does not rely on loop
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   static int pwm[2]; // [0] is left_pwm, [1] is right_pwm

   int p = calc_p(error);
   int d = calc_d(error, prev_error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p + d; // Speed up left wheel
      r_speed = base_speed - p - d; // Slow down right wheel
                      
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p - d; // Slow down left wheel
      r_speed = base_speed + p + d; // Speed up right wheel
    }

    l_speed = constrain(l_speed, 0 , max_speed);
    r_speed = constrain(r_speed, 0, max_speed);

    store_pwm(l_speed,r_speed);
  
    analogWrite(left_pwm_pin, l_speed);
    analogWrite(right_pwm_pin, r_speed);

    prev_error = error;

  // return pwm speeds
  pwm[0] = l_speed;
  pwm[1] = r_speed;
  return pwm;
}

void drive_car() { // is not a loop
  set_forward();
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);
  // store_data(error,sensor_values); // STORES ERRORS & CROSS PIECE
  control_car(error);
}

void stop_car() { // stop car
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
  digitalWrite(LED_Y, HIGH); // turn on yellow LED 
}

void duration(int encode_ct){ // looping function: drives car and stops after number of encoder counts
  while(true) {
    //Serial.println(avg_encoder());
    if (avg_encoder() >= encode_ct){
      stop_car();
      delay(500);
      output_data();
      return;
    }
    drive_car();
  }
}

#endif
