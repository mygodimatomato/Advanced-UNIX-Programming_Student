#include <sys/select.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void sleep_us(long int scs) {
    struct timeval tv;
    tv.tv_sec=scs/1000000;
    tv.tv_usec=scs%1000000;
    select(0,NULL,NULL,NULL,&tv); 
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        puts("Usage: ./q2 [time]");
        exit(0);
    }
    long int scs = atol(argv[1]);
    struct timeval ct;
    struct timeval nt;
    gettimeofday(&ct, NULL);
    sleep_us(scs);
    gettimeofday(&nt, NULL);
    long int fin = (nt.tv_sec-ct.tv_sec)*1000000l+(nt.tv_usec-ct.tv_usec);
    printf("Sleep time: %ld us\n",fin);
    return 0;
}
