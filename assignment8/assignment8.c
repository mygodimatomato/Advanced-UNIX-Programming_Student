#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

static void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR1) error");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR2) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");
}

static void TELL_PARENT(void)
{
    kill(getppid(), SIGUSR2); /* tell parent we’re done */
}

static void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for parent */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1); /* tell child we’re done */
}

static void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for child */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static int increment_counter(FILE *const file)
{
    int fn = fileno(file);
    char buf[4];
    ssize_t n = pread(fn,buf,3,0);
    buf[n]='\0';
    int num = 0;
    for(int i=0; i<n; i++) {
	num = num*10+(buf[i] - '0');
    }
    char nbuf[4];
    n = sprintf(nbuf,"%i",num+1);
    n = pwrite(fn,nbuf,n,0);
    return num+1;
}

int main(void)
{
    FILE *numfile = fopen("num.txt","w+");
    int fn = fileno(numfile);
    pwrite(fn,"0",1,0);
    pid_t pid = fork();
    if (pid < 0) {
	perror("fork failed");
	exit(1);
    }

    TELL_WAIT();
    if (pid == 0) { // Child
	while (1) {
	  int n = increment_counter(numfile);
          printf("Child incrementing, value: %i\n",n);
          TELL_PARENT();
          WAIT_PARENT(); 
	}
    } else { // Parent
        while (1) {
            WAIT_CHILD();
            int n = increment_counter(numfile);
            printf("Parent incrementing, value: %i\n",n);
            if (n == 100) {
                kill(pid, SIGKILL);
                exit(0);
            }
            TELL_CHILD(pid);
        }
    }

}
