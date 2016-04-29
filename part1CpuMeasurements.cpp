#include "part1CpuMeasurements.h"
#include <stdio.h>
#include "rdtsc.h"
#include <math.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <time.h>
//#include <time.h>

// Don't forget to execute program with  "taskset -c 0 ./a.out" to ensure
// that it executes on a single core

// Download rdtsc.h here:  (don't need to do this if you copied my folder)
// https://www.mcs.anl.gov/~kazutomo/rdtsc. h
// We might have to change line 18 to:   (don't do this yet!!)
//  __asm__ __volatile__ ("cpuid;" "rdtsc" : "=a"(lo), "=d"(hi));

// We might have to turn off caching at some point (don't do this yet)
// https://geteventstore.com/blog/20131218/disabling-disk-caching-in-ubuntu/
// you MIGHT** have to download hdparm here:
// https://sourceforge.net/projects/hdparm/

int main(){
	printf("hello world!!!!!!!! WOOOOOOO!! %d \n", getpid());

	// Calculate overhead of reading TIME
	int clockNumTrials = 100;
	double clockMean;
	double clockStDev;
	measureTimeMeasurement(clockNumTrials, clockMean, clockStDev);
    printf("Time Mean:  %0.2f,   Time Standard Deviation:  %0.2f \n", clockMean, clockStDev);



    return 0;
}

// function to get the data for 4.1.1  -  Operations: CPU Scheduleing 
// and OS services:  Measurement Overhead.  
// numTimesToTest:  number of times to test
// mean  and  stDev are passed by reference and will be updated with 
// the appropriate values
void measureTimeMeasurement(int numTrials, double &mean, double &stDev){
	double means[numTrials];
	for(int i=0; i<numTrials; i++){
		means[i] = measureTimeMeasurementHelper(1000);
		printf("Trial %d:  %0.2f \n", i, means[i]);
		calcStDev(means, numTrials);
		calcMean(means, numTrials);
		//usleep(100000);
	}
	mean = calcMean(means, numTrials);
	stDev = calcStDev(means, numTrials);
}

// helper function for measureTimeMeasurement
// this checks the time 1000 times and takes the mean
double measureTimeMeasurementHelper(int numTimesToTest) {
	unsigned long long results[numTimesToTest];
    unsigned long long beg, end;
    struct timespec test;
    pid_t pid;
    for(int i=0; i<numTimesToTest; i++){
	    beg = rdtsc();
	    for(int j=0; j<1000; j++){
	    	//dummy(1, 2, 3, 4, 5, 6, 7, 8);
	    	syscall(SYS_getpid);
/*
	    	pid = fork();
	    	if(pid==-1){
	    		fprintf(stderr, "can't fork, problem!!");
	    		//exit(0);
	    	} else if(pid == 0) {
	    		// child process, just exit
	    		_exit(0);
	    	} else {

	    	}
*/
	    }
   		end = rdtsc();
		//printf("measurementOverhead:  %llu\n", end-beg);
		// need to flush cache here?  Maybe not...
		//calcStDev(results, numTimesToTest);
		results[i] = end-beg;
    }
    return calcMean(results, numTimesToTest);
}

// dummy functions to test overhead of calling a function
void dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8){}
void dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7){}
void dummy(int x1, int x2, int x3, int x4, int x5, int x6){}
void dummy(int x1, int x2, int x3, int x4, int x5){}
void dummy(int x1, int x2, int x3, int x4){}
void dummy(int x1, int x2, int x3){}
void dummy(int x1, int x2){}
void dummy(int x1){}
void dummy(){}

// function to calculate the mean of an array
double calcMean(unsigned long long data[], int length){
	double answer = 0;
	for(int i=0; i<length; i++){
		answer += data[i];
	}
	answer = answer/length;
	return answer;
}

// function to calculate the standard deviation of an array
double calcStDev(unsigned long long data[], int length){
	double mean = 0;
	double stDev = 0;
	for(int i=0; i<length; i++){
		mean += data[i];
	}
	mean = mean/length;
	for(int i=0; i<length; i++){
		stDev += ((data[i]-mean)*(data[i]-mean));
	}
	stDev = stDev/length;
	return sqrt(stDev);

}

// function to calculate the mean of an array
double calcMean(double data[], int length){
	double answer = 0;
	for(int i=0; i<length; i++){
		answer += data[i];
	}
	answer = answer/length;
	return answer;
}

// function to calculate the standard deviation of an array
double calcStDev(double data[], int length){
	double mean = 0;
	double stDev = 0;
	for(int i=0; i<length; i++){
		mean += data[i];
	}
	mean = mean/length;
	for(int i=0; i<length; i++){
		stDev += ((data[i]-mean)*(data[i]-mean));
	}
	stDev = stDev/length;
	return sqrt(stDev);

}
