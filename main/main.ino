#include <ECE3.h>

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

  digitalWrite(left_dir_pin,HIGH);
  digitalWrite(left_nslp_pin,HIGH);
  
  digitalWrite(right_dir_pin,HIGH);
  digitalWrite(right_nslp_pin,HIGH);
}

// pwm signal ranges from: 0 - 255 

max_speed = 128;

int l_speed = 70;
int r_speed = 70;

int mins[8] = {756, 595,686,503,572,663,641,706};
int maxs[8] = {1744,1321,1658,964,1155,1718,1489,1794};

int calc_error() {
  int error;
  int weighted_sum = 0;
  int temp[8]={0,0,0,0,0,0,0,0};
  
  for (int i = 0; i < 8; i++) {
    temp[i] = sensor_values[i] - mins[i];
    if (temp[i] <=0) {
      temp[i]=0;
    } 
    temp[i] = temp[i] * 1000 / maxs[i];
    weighted_sum += temp[i] * weights[i];
  }
  error = weighted_sum / 8;

  return error;
}

void loop() {
  // analogWrite(left_pwm_pin, l_speed);
  // analogWrite(right_pwm_pin, r_speed);

  /*while (true) {
    ECE3_read_IR(sensor_values);

    //Serial.println(sensor_values);
    
    for (unsigned char i=0; i < 8; i++) {
      Serial.print(sensor_values[i]);
      Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    }
    Serial.println();
  }
  delay(100);
  */

}
