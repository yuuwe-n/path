#include <ECE3.h>

uint16_t sensorValues[8]; // sensor values: right -> left, 0 -> 7

const int left_nslp_pin=31; // nslp ==> awake & ready for PWM
const int left_dir_pin=29;
const int left_pwm_pin=40;

const int right_nslp_pin=11; // nslp ==> awake & ready for PWM
const int right_dir_pin=30;
const int right_pwm_pin=39;

const int LED_RF = 41;


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

int l_speed = 70;
int r_speed = 70;
int current_position=-40;
int increment_position = 4;
int number_samples=5;

void loop() {
  // analogWrite(left_pwm_pin, l_speed);
  // analogWrite(right_pwm_pin, r_speed);

  while (true) {
    ECE3_read_IR(sensorValues);

    //Serial.println(sensorValues);
    
    for (unsigned char i=0; i < 8; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    }
    Serial.println();
  }
  delay(100);

}
