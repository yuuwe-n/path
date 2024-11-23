#ifndef ERROR_H
#define ERROR_H

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

void calc_norm(uint16_t input[8], uint16_t output[8]) {
  uint16_t temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  for (int i = 0; i < 8; i++) {
    temp[i] = input[i] - mins[i];
    if (temp[i] <= 0) {
      temp[i] = 0;
    }
    temp[i] = temp[i] * 1000 / maxs[i];
    output[i] = temp[i]; // Store the result in the output array
  }
}

#endif
