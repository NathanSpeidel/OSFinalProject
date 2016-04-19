#ifndef _PART1CPUMEASUREMENTS_
#define _PART1CPUMEASUREMENTS_

void measureTimeMeasurement(int numTrials, double &mean, double &stDev);
double measureTimeMeasurementHelper(int numTimesToTest);
void dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
void dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7);
void dummy(int x1, int x2, int x3, int x4, int x5, int x6);
void dummy(int x1, int x2, int x3, int x4, int x5);
void dummy(int x1, int x2, int x3, int x4);
void dummy(int x1, int x2, int x3);
void dummy(int x1, int x2);
void dummy(int x1);
void dummy();
double calcMean(unsigned long long data[], int length);
double calcStDev(unsigned long long data[], int length);
double calcMean(double data[], int length);
double calcStDev(double data[], int length);




#endif
