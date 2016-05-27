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
	//printf("hello world!!!!!!!! WOOOOOOO!! \n");

	// Calculate overhead of reading TIME
	int numTrials = 100000;
	int i=0;
	double mean;
	double stDev;
	unsigned long long results[numTrials];
  	unsigned long long beg, end;
  	for(i=0; i<numTrials; i++){
		beg = rdtsc();
		end = rdtsc();
		results[i] = end-beg;
  	}

  	mean = calcMean(results, numTrials);
  	stDev = calcStDev(results, numTrials);
	//printf("%lld \n", end-beg);
 	printf("Time Mean:  %0.2f,   Time Standard Deviation:  %0.2f \n", mean, stDev);



    return 0;
}

/*
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
*/

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
