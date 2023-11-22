#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;


int main(void)
{
    FILE *numfile = fopen("num.txt","r+");
    fputs("0",numfile);
    increment_counter(numfile);
}
