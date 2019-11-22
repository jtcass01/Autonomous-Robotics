#ifndef SINGLE_VARIABLE_KALMAN_FILTER
#define SINGLE_VARIABLE_KALMAN_FILTER

#define RUNNING_AVERAGE_LOOKBACK_SIZE 7

typedef struct {
  int previousReadings[RUNNING_AVERAGE_LOOKBACK_SIZE];
  int index;
  int average;
  int full;
} RunningAverage;

void RA_Init(RunningAverage *);
int RA_Update(RunningAverage *, const float);

#endif
