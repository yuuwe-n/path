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
#endif
