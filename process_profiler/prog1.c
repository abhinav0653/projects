#include <stdio.h>
#include <sys/resource.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
//struct rusage {
//               struct timeval ru_utime; /* user CPU time used */
//               struct timeval ru_stime; /* system CPU time used */
//               long   ru_maxrss;        /* maximum resident set size */
//               long   ru_ixrss;         /* integral shared memory size */
//               long   ru_idrss;         /* integral unshared data size */
//               long   ru_isrss;         /* integral unshared stack size */
//               long   ru_minflt;        /* page reclaims (soft page faults) */
//               long   ru_majflt;        /* page faults (hard page faults) */
//               long   ru_nswap;         /* swaps */
//               long   ru_inblock;       /* block input operations */
//               long   ru_oublock;       /* block output operations */
//               long   ru_msgsnd;        /* IPC messages sent */
//               long   ru_msgrcv;        /* IPC messages received */
//               long   ru_nsignals;      /* signals received */
//               long   ru_nvcsw;         /* voluntary context switches */
//               long   ru_nivcsw;        /* involuntary context switches */
//           };

//     struct timeval {
//         time_t tv_sec;  /* second */
//         long   tv_usec; /* microsecond */
//     };

struct rusage current1,current2;
struct timeval tval_before, tval_after, tval_result;

void calculate()
{
	long user_time_us = current2.ru_utime.tv_usec-current1.ru_utime.tv_usec;
	long user_time_s = current2.ru_utime.tv_sec-current1.ru_utime.tv_sec;
	long system_time_us = current2.ru_stime.tv_usec-current1.ru_stime.tv_usec;
	long system_time_s = current2.ru_stime.tv_sec-current1.ru_stime.tv_sec;
	double user_time = (double)user_time_s + ((double)user_time_us/1000000);
	double system_time = (double)system_time_s + ((double)system_time_us/1000000);
	double total_time = (double)tval_result.tv_sec + ((double)tval_result.tv_usec/1000000);
	double exec_time =  user_time + system_time;

	FILE* fp = fopen("log.txt","r+");
	
	fprintf(fp,"************Only Computation************\n\n");
	fprintf(fp,"Turnaround time:%lf\n",total_time);
	fprintf(fp,"User time:%lf\n",user_time);
	fprintf(fp,"System time:%lf\n",system_time);
	fprintf(fp,"Running time:%lf\n",exec_time);
	fprintf(fp,"Waiting time:%lf\n",total_time-exec_time);
	fprintf(fp,"Penalty ratio:%lf\n",total_time/exec_time);

	fprintf(fp,"\n\n\n");
	fprintf(fp,"************executing procinfo*************");
	system("procinfo >> log.txt");
}

void startprofiling()
{
	gettimeofday(&tval_before,NULL);
//	time_t begin = time(NULL);
	getrusage(RUSAGE_SELF, &current1);
}

void stopprofiling()
{
	getrusage(RUSAGE_SELF, &current2);
	gettimeofday(&tval_after,NULL);
	timersub(&tval_after,&tval_before,&tval_result);
	calculate();
}
void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		stopprofiling();
		printf("Received sigint\n");
		exit(0);
	}

}
int main(int argc,char** argv)
{
	if(signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch sigint\n");
	startprofiling();
	int a;
	while(1){
	  a++	;
	  a--   ;	
	}

	

}
