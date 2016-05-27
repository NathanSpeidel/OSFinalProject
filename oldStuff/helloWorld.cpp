#include <stdio.h>
#include "rdtsc.h"

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
	int numTrials = 10;
	//unsigned long long results[numTrials];
    //unsigned long long beg, end;
	for(int i=0; i<numTrials; i++){
		//asm("");
	    //beg = rdtsc();
    	//syscall(SYS_getpid);
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
   		//end = rdtsc();
		//results[i] = end-beg;
		//printf("  %lld \n", end-beg);
	}


    return 0;
}
