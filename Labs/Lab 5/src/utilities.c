#include "utilities.h"

int bind(int value, int lowerBound, int upperBound) {
  if (value < lowerBound) {
    return lowerBound;
  } else if (value > upperBound) {
    return upperBound;
  } else {
    return value;
  }
}


void printData(char *dataLabel, int *data, int dataSize) {
    printf("%s : [", dataLabel);
    int dataIndex = 0;
    while(dataIndex++ < dataSize) {
        if(dataIndex < dataSize) {
	        printf("%d, ", data[dataIndex]);
        } else {
	        printf("%d", data[dataIndex]);
        }
    }
    printf("]\n");
}
