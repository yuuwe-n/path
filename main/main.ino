#include <ECE3.h>
#include <init.h>

uint16_t sensor_values[8]; // sensor values: right -> left, 0 -> 7

const int left_nslp_pin=31;
const int left_dir_pin=29;
const int left_pwm_pin=40;

const int right_nslp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;

const int bump_0 = 24; // this bump is on the right
const int bump_5 = 28; // lets use this bump because it is on the left side
// TRUE => bump is not switched
// FALSE => bump is switched

const int LED_RF = 41;

// pwm signal ranges from: 0 - 255 
int max_speed = 127;
int base_speed = 40;

int l_speed = base_speed;
int r_speed = base_speed;

int prev_error = 0;

int weights[8] = {-15, -14, -12, -8, 8, 12, 14, 15};
int mins[8] = {756, 595,686,503,572,663,641,706};
int maxs[8] = {1744,1321,1658,964,1155,1718,1489,1794};

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

  resetEncoderCount_left();
  resetEncoderCount_right();

  delay(4000); // wait for setup
}

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
  digitalWrite(left_dir_pin,LOW);
  digitalWrite(right_dir_pin,HIGH);
}

void set_left() {
  digitalWrite(left_dir_pin,HIGH);
  digitalWrite(right_dir_pin,LOW);
}

int avg_encoder() {
  int l_encoder = getEncoderCount_left();
  int r_encoder = getEncoderCount_right();
  return ((l_encoder + r_encoder) / 2.0);
}


// you may want to reset, encoder after completing a certain duration
int revs() { // returns wheel revolutions
  int revolutions = avg_encoder() / 360;
  return revolutions;
}

void test_encoder() {
  set_nlsp(true);
  analogWrite(left_pwm_pin, 40);
  analogWrite(right_pwm_pin, 40);
  Serial.print(avg_encoder());
  Serial.print('\t');
  Serial.print(revs());
  Serial.println();
}

int calc_error(uint16_t input[8]) { // takes input of sensor values

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

  store_data(error); // MAY NEED TO REMOVE IN DRIVING
  
  return error;
}

void test_real_time(bool wheels = false) { // this function should loop
  
  set_nlsp(wheels); // TURN OFF WHEELS
  
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

float K_P = 0.01;
float K_D = 0.005;

int calc_p(int error) {
  int p = K_P * abs(error);
  return p;
}

int calc_d(int error) {
  int d = K_D * abs(error);
  return d;
}

int* control_car(int error) {
   //*  error > 0 : track is to the LEFT
   //* error < 0 : track is to the RIGHT

   static int pwm[2]; // [0] is left_pwm, [1] is right_pwm

   int p = calc_p(error);

   if (error < 0) { // error < 0, Track is to the RIGHT, steer RIGHT
      l_speed = base_speed + p; // Speed up left wheel
      r_speed = base_speed - p; // Slow down right wheel                  
    } else { // error > 0, Track is to the LEFT, steer LEFT
      l_speed = base_speed - p; // Slow down left wheel
      r_speed = base_speed + p; // Speed up right wheel
    }

  //l_speed = constrain(l_speed, 0, max_speed);
  //r_speed = constrain(r_speed, 0, max_speed);
  
  analogWrite(left_pwm_pin, l_speed);
  analogWrite(right_pwm_pin, r_speed);

  pwm[0] = l_speed;
  pwm[1] = r_speed;
  return pwm;
}

void drive() {
  set_forward();
  ECE3_read_IR(sensor_values);
  int error = calc_error(sensor_values);
  control_car(error);
}

const int DATA_COUNT = 1500;
short count = 0;
short data[DATA_COUNT];

void store_data(int error) {
  data[count] = error;
  count += 1;
}

unsigned long startTime;
const unsigned long delayTime = 10000;
void test_store_data() {
  drive();
  if (millis() - startTime >= delayTime) {
        stop_car();      // Call the function after 10 seconds
        startTime = millis();  // Reset startTime if you want to call the function every 10 seconds
  }
}

void output_data() {
  while (true){
    if (!digitalRead(bump_5)) {
      for (int i = 0; i < DATA_COUNT; i++) {
        Serial.print(data[i]); Serial.print('\t');
      }
    }
  }
}

void stop_car() {
  analogWrite(left_pwm_pin, 0);
  analogWrite(right_pwm_pin, 0);
  analogWrite(LED_RF, HIGH); // turn on yellow LED 

  output_data();
}

void duration(int max_revs){ // stops after number of revolutions
  if (revs() <= max_revs){
    stop_car();
    return;
  }
  drive();
}

void loop() {
  //test_real_time(false);
  //drive();
  
}

  /* TODO:
   *  - test wheel direction / variable names for left/right
   *  - test store_data
   *  - test stop_car
   *  - test output_data
   *  - test duration
   *  - 360 degree function
   *  - donut function
   *  - bump => change k_p, k_d
   */
