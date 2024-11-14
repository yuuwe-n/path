#include <ECE3.h>

/*
 * TODO: FIX P AND D TERMS
 * 
 * 
 */

uint16_t sensor_values[8]; // sensor values: right -> left, 0 -> 7

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;

const int right_nslp_pin=11; // nslp ==> awake & ready for PWM
const int right_dir_pin=30;
const int right_pwm_pin=39;

const int LED_RF = 41;

int weights[8] = {-15, -14, -12, -8, 8, 12, 14, 15};

void setup() {
  ECE3_Init();
  
  Serial.begin(9600);
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

  delay(4000); // wait for setup
}

// pwm signal ranges from: 0 - 255 

int max_speed = 127;
int base_speed = 40;

int l_speed = base_speed;
int r_speed = base_speed;


float K_P = 0.01;
float K_D = 0.005;

int prev_error = 0;


int mins[8] = {756, 595,686,503,572,663,641,706};
int maxs[8] = {1744,1321,1658,964,1155,1718,1489,1794};

/*
int mins[8] = {706, 641, 663, 572, 503, 686, 595, 756};
int maxs[8] = {1794, 1489, 1718, 1155, 964, 1658, 1321, 1744};
*/

void nlsp_low() {
  digitalWrite(left_nslp_pin, LOW);
  digitalWrite(right_nslp_pin, LOW);
}

void test() { // this function will loop
  
  nlsp_low(); // TURN OFF WHEELS
  
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);

  int* pwm = control_car(error);
  int left_pwm = pwm[0];
  int right_pwm = pwm[1];

  Serial.print(left_pwm);
  Serial.print("\t | \t");

  Serial.print(right_pwm);
  Serial.print("\t | \t");

  Serial.print(error);
  Serial.print("\t | \t");
  for (unsigned char i = 0; i < 8; i++)
  {
    Serial.print(sensor_values[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(500);
}

void set_forward() {
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(right_dir_pin,LOW);
}

void set_right() {
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(right_dir_pin,HIGH);
}

void set_left() {
  digitalWrite(left_dir_pin,HIGH);
  digitalWrite(right_dir_pin,LOW);
}

int calc_error(uint16_t input[8]) { // takes input of sensor values

/*
 * Positive error : black line is to the left => ERROR = -40mm => error > 0 : steer to the right
 * Negative error : black line is to the right => ERROR = 40mm => error < 0 : steer to the left
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

int calc_d(int error) {
  int d = K_D * abs(error);
  return d;
}

int* control_car(int error) {
   //*  error > 0 : track is to the left
   //* error < 0 : track is to the right

   int pwm[2];

   int p = calc_p(error);

  if (error < 0) { // error < 0, Track is to the left, steer left !!! THIS WORKS, ADJUST K_P
      l_speed = base_speed;                             // Keep left wheel at base speed
      r_speed = base_speed + p; // Speed up right wheel to steer right                     
   } else { // error > 0, Track is to the right, steer right
      l_speed = base_speed + p; // Speed up right wheel to steer right
      r_speed = base_speed;                             // Keep left wheel at base speed
   }

  //l_speed = constrain(l_speed, 0, max_speed);
  // r_speed = constrain(r_speed, 0, max_speed);
  analogWrite(left_pwm_pin, l_speed);
  analogWrite(right_pwm_pin, r_speed);

  l_speed=0;
  r_speed=0;

  pwm[0] = l_speed;
  pwm[1] = r_speed;
  return pwm;
  
}

void loop() {
  set_forward(); // make sure direction of car is forward

  test();

  //ECE3_read_IR(sensor_values);
  //int error = calc_error(sensor_values);
  
  //control_car(error);
  
  }
