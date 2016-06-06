#ifndef _PART1CPUMEASUREMENTS_
#define _PART1CPUMEASUREMENTS_

void* threadFunction(void *void_pointer);
void measureTimeMeasurement(int numTrials, double &mean, double &stDev);
double measureTimeMeasurementHelper(int numTimesToTest);
int dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
int dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7);
int dummy(int x1, int x2, int x3, int x4, int x5, int x6);
int dummy(int x1, int x2, int x3, int x4, int x5);
int dummy(int x1, int x2, int x3, int x4);
int dummy(int x1, int x2, int x3);
int dummy(int x1, int x2);
int dummy(int x1);
int dummy();
double calcMean(unsigned long long data[], int length);
double calcStDev(unsigned long long data[], int length);
double calcMean(double data[], int length);
double calcStDev(double data[], int length);




#endif
