#include <stdio.h>
#include <pthread.h>

// heavily simplified logic from pthread_barrier_init.c, pthread_barrier_wait.c and pthread_barrier_destroy.c from glibc.
// Other references: http://sourceware.org/git/?p=glibc.git;a=blob;f=nptl/DESIGN-barrier.txt;h=23463c6b7e77231697db3e13933b36ce295365b1;hb=HEAD

typedef struct barrier_type {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int s_count;
    int count;
    int cycle;
} barrier_t;
static barrier_t b;

void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    int cycle = barrier->cycle; // Determines whether we are waiting for all threads to initialize
    barrier->count--;
    if(barrier->count == 0) { // release all threads if all have started.
        barrier->cycle = !barrier->cycle;
        barrier->count = barrier->s_count;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        while(cycle == barrier->cycle) { // release mutex as long as count isn't 0
            int t = pthread_cond_wait(&barrier->cond, &barrier->mutex);
            if (t != 0) break;
        }
    }
    pthread_mutex_unlock(&barrier->mutex);
}

void* thr_fn(void* a) {
    barrier_wait(&b);
    printf("Thread %lu running\n", (unsigned long)pthread_self());
    return((void*)1);
}

int main() {
    b.count = b.s_count = 5;
    b.cycle = 0;
    pthread_mutex_init(&b.mutex, NULL);
    pthread_cond_init(&b.cond, NULL);

    pthread_t pt[5];
    for(int i=0; i<5; i++) {
        printf("Starting thread %d\n", i);
        pthread_create(&pt[i], NULL, thr_fn, (void*)1);
    }
    for(int i=0;i<5; i++) {
        pthread_join(pt[i],NULL);
    }
    return 0;
}
