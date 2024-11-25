#ifndef CROSS_H
#define CROSS_H

// ADJUST CROSS_PIECE DETECTION THRESHOLD
bool detect_crosspiece(uint16_t sensor_values[8]) {
  // Check if all inner sensors (indices 2 to 5) are greater than 2400
  for (int i = 2; i <= 5; i++) {
    if (sensor_values[i] <= 2400) {
      return false;
    }
  }
  return true;
}

int real_max[8] = { 2500 , 1916 , 2344 , 1467 , 1727 , 2381 , 2130 , 2500 };

int consecutive_real_cross = 0;

bool detect_real_cross(uint16_t sensor_values[8]) {
  // Check if all sensor values are above 95% of real_max
  bool above_threshold = true;
  for (int i = 0; i < 8; i++) {
    int lower_bound = real_max[i] * 0.95; // 95% of real_max
    if (sensor_values[i] < lower_bound) { // Check if below the lower bound
      above_threshold = false;
      break;
    }
  }

  // Increment or reset consecutive detection counter
  if (above_threshold) {
    consecutive_real_cross += 1;
  } else {
    consecutive_real_cross = 0;
  }

  // Return true if detected two times in a row
  return consecutive_real_cross >= 2;
}

/*
bool detect_real_cross(uint16_t sensor_values[8]) {
  // Check if all sensor values are above 90% of real_max
  bool above_threshold = true;
  for (int i = 0; i < 8; i++) {
    int lower_bound = real_max[i] * 0.95; // 90% of real_max
    if (sensor_values[i] < lower_bound) { // Check if below the lower bound
      above_threshold = false;
      break;
    }
  }

  return above_threshold;
}
*/

int block_count = 0;
bool inside_block = false; // Tracks whether we are currently in a block

void track_block(bool real_cross) {
    if (real_cross) {
        if (!inside_block) {
            // Entering a new block
            inside_block = true;
            block_count++; // Increment block count for the new block
        }
    } else {
        // Exiting a block
        inside_block = false;
    }
}

#endif
