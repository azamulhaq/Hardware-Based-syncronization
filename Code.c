#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t sem;

void *thread_func(void *arg) {
    int *id = (int *)arg;
    printf("Thread %d waiting for semaphore...\n", *id);
    sem_wait(&sem);
    printf("Thread %d acquired semaphore!\n", *id);
    sleep(1);  // simulate some work being done
    sem_post(&sem);
    printf("Thread %d released semaphore!\n", *id);
    return NULL;
}

int main() {
    int noOfThread;
    printf("Enter number of threads:");
    scanf("%d",&noOfThread);
    pthread_t threads[noOfThread];
    sem_init(&sem, 0, 3);  // initialize semaphore with count of 3

    // create threads
    for (int i = 0; i < noOfThread; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, thread_func, id);
    }

    // join threads
    for (int i = 0; i < noOfThread; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);  // destroy semaphore

    return 0;
}