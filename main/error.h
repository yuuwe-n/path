#ifndef ERROR_H
#define ERROR_H

int calc_error(uint16_t input[8]) {
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

void calc_norm(uint16_t input[8], uint16_t output[8]) { // not working
  uint16_t temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  for (int i = 0; i < 8; i++) {
    temp[i] = input[i] - mins[i];
    if (temp[i] <= 0) {
      temp[i] = 0;
    }
    temp[i] = temp[i] * 1000 / maxs[i];

    if (temp[i] >= 1000) {
      temp[i] = 1000;
    }

    output[i] = temp[i]; // Store the result in the output array
  }
}

#endif
