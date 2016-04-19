#include "part1CpuMeasurements.h"
#include <stdio.h>
#include "rdtsc.h"
//#include <time.h>

int main(){
	printf("hello world!\n");
	double mean_;
	double stDev_;
	measurementOverhead(10, mean_, stDev_);
    printf("Mean:  %0.2f,   Standard Deviation:  %0.2f \n", mean_, stDev_);
    return 0;
}

void measurementOverhead(int numTimesToTest, double& mean_, double& stDev_) {
	unsigned long long results[numTimesToTest];
    unsigned long long beg, end;

    for(int i=0; i<numTimesToTest; i++){
	    beg = rdtsc();
   		end = rdtsc();
		printf("measurementOverhead:  %llu\n", end-beg);
		results[i] = end-beg;
    }

    mean_ = mean(results);
    stDev_ = stDev(results);
}

double mean(unsigned long long data[]){
	return 1.2;
}

double stDev(unsigned long long data[]){
	return 1.3;
}
