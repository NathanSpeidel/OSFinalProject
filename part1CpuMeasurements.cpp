#include "part1CpuMeasurements.h"
#include <stdio.h>
#include "rdtsc.h"
#include <math.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>
//#include <time.h>

// Don't forget to disable 3 of the 4 cores!!   This is done by executing 
// echo 0 > /sys/devices/system/cpu/cpu1/online
// for each of the cpus (cpu1, cpu2 and cpu3 (cpu0 cant be turned off))
// you can also see which CPUs are online with  "lscpu"
// Or, alternitively
// You can execute program with  "taskset -c 0 ./a.out" to ensure
// that it executes on a single core

// Also don't forget that to use the pthread stuff you have to append 
// "-lpthread"  to the very end of the compile command to gcc

// Download rdtsc.h here:  (don't need to do this if you copied my folder)
// https://www.mcs.anl.gov/~kazutomo/rdtsc. h
// We might have to change line 18 to:   (don't do this yet!!)
//  __asm__ __volatile__ ("cpuid;" "rdtsc" : "=a"(lo), "=d"(hi));

// We might have to turn off caching at some point (don't do this yet)
// https://geteventstore.com/blog/20131218/disabling-disk-caching-in-ubuntu/
// you MIGHT** have to download hdparm here:
// https://sourceforge.net/projects/hdparm/

int tempGlobal = 88;

int main(){
	printf("hello world!!!!!!!! WOOOOOOO!! %d \n", tempGlobal);

	// Calculate overhead of reading TIME
	int clockNumTrials = 1;
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
		means[i] = measureTimeMeasurementHelper(1);
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
    pthread_t thread1;
    int temp;
	int myPipe[2];
    for(int i=0; i<numTimesToTest; i++){
	    //beg = rdtsc();
	    //beg = 0;
	    //for(int j=0; j<10; j++){
	    	//asm("");	// command Marc talked about that should order things?
	    	//temp = dummy(temp, temp, temp, temp, temp, temp, temp, temp);
	    	//tempGlobal = dummy(temp);
	    	//asm("");
	    	//syscall(SYS_getpid);
	    	
	    	/*
	    	if(pthread_create(&thread1, NULL, threadFunction, &temp)){
	    		fprintf(stderr, "Something went wrong creating thread!!");
	    		printf("something went wrong creating thread!!!!");
	    		return 1;
	    	}
	    	if(pthread_join(thread1, NULL)){
	    		printf("error joining thread!  :(");
	    		return 2;
	    	}
	    	//printf("threads joined now?");
			*/

			temp = pipe(myPipe);
			if(temp==-1){
				perror("problem making pipe!");
			}
	    	pid = fork();
	    	if(pid==0){  // Child process
	    		close(myPipe[0]);
	    		//sleep(.1);
	    		beg = rdtsc();
	    		write(myPipe[1], &beg, sizeof(beg));
	    		pthread_yield();
	 		   	_exit(1);
	    	} else if(pid > 0) {
	    		// parent process;
	    		read(myPipe[0], &beg, sizeof(beg));
	    		end = rdtsc();
	    		//wait(NULL);
		    	//printf("Parent process. beg = %lld \n", beg);
	    	} else {
	    		// error
	    		printf("Problem using fork()!!!");
	    		perror("problem executing fork()");
	    		exit(1);
	    	}
	    	

	    //}
   		//end = rdtsc();
   		
   		//tempGlobal = temp+temp;
   		//temp = temp+temp;
		//printf("measurementOverhead:  %llu\n", end-beg);
		// need to flush cache here?  Maybe not...
		//calcStDev(results, numTimesToTest);
		results[i] = end-beg;
		//temp = temp+8;
    }
    return calcMean(results, numTimesToTest);
}

// function to run in the kernel thread
void* threadFunction(void *void_pointer){
	//printf("in thread Function");
	return NULL;
}

// dummy functions to test overhead of calling a function
int dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8){return x1+x2+x3+x4+x5+x6+x7+x8;}
int dummy(int x1, int x2, int x3, int x4, int x5, int x6, int x7){return x1+x2+x3+x4+x5+x6+x7;}
int dummy(int x1, int x2, int x3, int x4, int x5, int x6){return x1+x2+x3+x4+x5+x6;}
int dummy(int x1, int x2, int x3, int x4, int x5){return x1+x2+x3+x4+x5;}
int dummy(int x1, int x2, int x3, int x4){return x1+x2+x3+x4;}
int dummy(int x1, int x2, int x3){return x1+x2+x3;}
int dummy(int x1, int x2){return x1+x2;}
int dummy(int x1){return x1+1;}
int dummy(){int test = tempGlobal; return test;}

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
