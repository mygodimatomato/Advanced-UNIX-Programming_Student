#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define MAXCHILD 1024
static void sig_handler(int);

void setAlarm(int sec){
	/* do something here ... */
	if (fork() == 0){
		if (signal(SIGALRM, sig_handler) == SIG_ERR)
		{
			printf("error: SIGALRM handler\n");
			exit(0);
		}
		if (signal(SIGUSR2, sig_handler) == SIG_ERR)
		{
			printf("error: SIGUSR2 handler\n");
			exit(0);
		}
	alarm(sec);
	while(1)
		pause();
	}
}
void clearAlarm(){
	/* do something here ... */
	kill(0, SIGUSR2);
}
int main (void) {
	// ...
	if (signal(SIGALRM, SIG_IGN) == SIG_ERR)
	{
		printf("error: SIGALRM handler of parent\n");
		exit(0);
	}
	if (signal(SIGUSR2, SIG_IGN) == SIG_ERR)
	{
		printf("error: SIGUSR2 handler parent\n");
		exit(0);
	}

	/* You should copy and paste these test cases to your implementation */
	setAlarm(2); //set 2 sec alarm at 0s, will finish at 2s after execution
	sleep(1);
	setAlarm(6); //set 6 sec alarm at 1s, will finish at 7s after execution
	sleep(1);
	setAlarm(3); //set 3 sec alarm at 2s, will finish at 5s after execution
	sleep(4);
	clearAlarm(); //clear all alarms at 6s after execution
	// ...
	return 0;
}

static void sig_handler(int signo)
{
	if (signo == SIGALRM)
	{
		printf("Alarm!\n");
		exit(0);
	}
	else if (signo == SIGUSR2)
	{
		exit(0);
	}
}


