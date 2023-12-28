// I want to implement a program that will create three thread, which is T1, T2, T3.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


// T1 needs to handle the signal SIGINT
void *T1_handler(void *arg){
  sigset_t set;
  int sig;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  pthread_sigmask(SIG_BLOCK, &set, NULL);
  sigwait(&set, &sig); // block until a signal is received, and then call
  printf("T1 handling SIGINT\n");
  return NULL;
}

// T2 needs to handle the signal SIGTERM
void *T2_handler(void *arg){
  sigset_t set;
  int sig;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  pthread_sigmask(SIG_BLOCK, &set, NULL);
  sigwait(&set, &sig); // block until a signal is received, and then call
  printf("T2 handling SIGTERM\n");
  return NULL;
}

// T3 needs to handle the signal SIGUSR1
void *T3_handler(void *arg){
  sigset_t set;
  int sig;
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  pthread_sigmask(SIG_BLOCK, &set, NULL);
  sigwait(&set, &sig); // block until a signal is received, and then call
  printf("T3 handling SIGUSR1\n");
  return NULL;
}

int main(){

  sigset_t set;
  sigfillset(&set);
  pthread_sigmask(SIG_BLOCK, &set, NULL);

  // initialize the thread
  pthread_t T1, T2, T3;
  pthread_create(&T1, NULL, T1_handler, NULL);
  pthread_create(&T2, NULL, T2_handler, NULL);
  pthread_create(&T3, NULL, T3_handler, NULL);

  return 0;
}