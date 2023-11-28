#include <stdio.h>
#include <pthread.h>

// heavily simplified logic from pthread_barrier_init.c, pthread_barrier_wait.c and pthread_barrier_destroy.c from glibc.
// Other references: http://sourceware.org/git/?p=glibc.git;a=blob;f=nptl/DESIGN-barrier.txt;h=23463c6b7e77231697db3e13933b36ce295365b1;hb=HEAD

typedef struct barrier_tag {
    pthread_mutex_t mutex;
    pthread_cond_t cv;
    int threshold;
    int counter;
    int cycle
} barrier_t;
static barrier_t b;
int barrier_wait (barrier_t *barrier)
{
    int status, cancel, tmp, cycle;
    status = pthread_mutex_lock (&barrier->mutex);
    if (status != 0)
        return status;

    cycle = barrier->cycle; // Determines ordering

    if (--barrier->counter == 0) {
        barrier->cycle = !barrier->cycle;
        barrier->counter = barrier->threshold;
        status = pthread_cond_broadcast (&barrier->cv);
        if (status == 0)
            status = -1;
    } else {
        pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &cancel);

        while (cycle == barrier->cycle) {
            status = pthread_cond_wait (
                    &barrier->cv, &barrier->mutex);
            if (status != 0) break;
        }

        pthread_setcancelstate (cancel, &tmp);
    }
    pthread_mutex_unlock (&barrier->mutex);
    return status;
}


void* thr_fn(void* a) {
    int n = barrier_wait(&b);
    //printf("status=%i\n",n);
    printf("Thread %lu running\n", (unsigned long)pthread_self());
    return((void*)1);
}

int main() {
    b.counter = b.threshold = 5;
    b.cycle = 0;
    pthread_mutex_init(&b.mutex, NULL);
    pthread_cond_init(&b.cv, NULL);

    pthread_t pt[5];
    for (int i=0; i<5; i++) {
        printf("Starting thread %d\n", i);
        pthread_create(&pt[i], NULL, thr_fn, (void*)1);
    }
    for (int i=0;i<5; i++) {
        pthread_join(pt[i],NULL);
    }
    return 0;
}
