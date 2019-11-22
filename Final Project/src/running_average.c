#include "running_average.h"

void RA_Init(RunningAverage *runningAverage) {
  runningAverage->index = 0;
  runningAverage->full = 0;
  runningAverage->average = 0;
}

int RA_Update(RunningAverage *runningAverage, const float reading) {
  int newAverage = 0;
  int i = 0;
  runningAverage->previousReadings[runningAverage->index++] = reading;

  if (runningAverage->index == RUNNING_AVERAGE_LOOKBACK_SIZE) {
    runningAverage->index = 0;
    runningAverage->full = 1;
  }

  if (runningAverage->full) {
    for (i = 0; i < RUNNING_AVERAGE_LOOKBACK_SIZE; i++) {
      newAverage += runningAverage->previousReadings[i];
    }

    runningAverage->average = (int) (newAverage / RUNNING_AVERAGE_LOOKBACK_SIZE);
  } else {
    for (i = 0; i < runningAverage->index; i++) {
      newAverage += runningAverage->previousReadings[i];
    }

    runningAverage->average = (int) (newAverage / runningAverage->index);
  }

  return runningAverage->average;
}
