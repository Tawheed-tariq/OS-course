// gcc -pthread 1_producer_consumer.c -o 1_producer_consumer
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>
#include<semaphore.h>

#define MAXSIZE 5

sem_t mutex;
sem_t full;
sem_t empty;

int queue[MAXSIZE];
int head = 0;
int tail = 0;

void *producer(void *arg){
    printf("running producer thread \t\t");
    int data = (intptr_t)arg;

    sem_wait(&empty);
    sem_wait(&mutex);
        
    queue[head] = data;
    printf("produced ................ %d\n\n", data);
    head = (head + 1) % MAXSIZE;
    sem_post(&mutex);
    sem_post(&full);
}

void *consumer(){
    printf("running consumer thread \t\t");
    sem_wait(&full); // -1
    sem_wait(&mutex);
    
    int data = queue[tail];
    printf("Consumed _______________ %d\n\n", data);
    tail = (tail + 1) % MAXSIZE;

    sem_post(&mutex);
    sem_post(&empty);
}

int main(){
    pthread_t producer_thread , consumer_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0 , MAXSIZE);
    
    for(int i = 0; i < MAXSIZE; i++){
        pthread_create(&producer_thread, NULL, producer, (void *)(intptr_t)(i + 10));
        pthread_create(&consumer_thread, NULL, consumer, NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
}