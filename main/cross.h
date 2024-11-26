#ifndef CROSS_H
#define CROSS_H

// ADJUST CROSS_PIECE DETECTION THRESHOLD

int consecutive_cross = 0;

// check inner 4 sensors
bool detect_c(uint16_t norm_values[8]) {
  bool above_threshold = true;
  
  for (int i = 2; i <= 5; i++) {
    if (norm_values[i] < 1000) {
      above_threshold = false;
      break;
    }
  }
  return above_threshold;
}

int cross_2 = 0;
bool detect_cross_2(uint16_t norm_values[8]) {
  bool above_threshold = true;
  
  for (int i = 0; i <= 4; i++) {
    if (norm_values[i] < 1000) {
      above_threshold = false;
      break;
    }
  }
  return above_threshold;
}

// check inner 4 sensors
bool detect_cross(uint16_t norm_values[8]) {
  bool above_threshold = true;
  
  for (int i = 2; i <= 5; i++) {
    if (norm_values[i] < 1000) {
      above_threshold = false;
      break;
    }
  }
  if (above_threshold) {
    consecutive_cross += 1;
  } else {
    consecutive_cross = 0;
  }

  return consecutive_cross >= 2;
}




int block_count = 0;
bool inside_block = false; // Tracks whether we are currently in a block

void track_block(bool cross) {
    if (cross) {
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


/*
bool detect_c(uint16_t norm_values[8]) {
  int count = 0;

  // Check sensors from index 0 to 7 (non-inclusive of 8)
  for (int i = 0; i < 8; i++) {
    if (norm_values[i] >= 1000) {
      count++;
      if (count >= 4) {
        return true; // Return true as soon as 4 sensors meet the condition
      }
    }
  }
  return false; // Less than 4 sensors have values >= 1000
}

bool detect_cross(uint16_t norm_values[8]) {
  int count = 0;

  // Count sensors with values >= 1000 from index 0 to 7
  for (int i = 0; i < 8; i++) {
    if (norm_values[i] >= 1000) {
      count++;
    }
  }

  // Check if at least 4 sensors meet the condition
  if (count >= 4) {
    consecutive_cross += 1; // Increment consecutive count
  } else {
    consecutive_cross = 0; // Reset if condition is not met
  }

  // Return true if detected two times in a row
  return consecutive_cross >= 2;
}
*/

#endif
