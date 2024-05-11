#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>

sem_t mutex;
sem_t wrt;
sem_t order;
int read_count = 0;


void *reader(void *arg){
    sem_wait(&order); //if order = 0, then it goes to -ive and reader has to wait, if order > 0 reader can read
    sem_wait(&mutex);
    read_count++;
    if(read_count == 1)
        sem_wait(&wrt); //if first reader then acquire lock so that no writer can access
    sem_post(&mutex);

    int index = (intptr_t)arg;
    char buf[10];
    int fd = open("db.txt", O_RDONLY | O_CREAT, 0644);
    pread(fd, buf, 10, index*2); //reads from the index*2 index of file
    printf("reader {\n %s\n}\n\n", buf);

    sem_wait(&mutex);
    read_count--;
    if(read_count == 0)
        sem_post(&wrt); //if the last reader then release lock
    sem_post(&mutex);
}

void *writer(){
    sem_wait(&wrt);

    printf("writer ______________________\n\n");
    char buf[100] = "This is an example text been written in db.txt for representation of readers writers problem";
    int fd = open("db.txt", O_WRONLY | O_CREAT, 0644);
    write(fd, buf, strlen(buf));

    sem_post(&wrt);
    sem_post(&order); //increase the value of order so that reader can read
}

int main(){
    pthread_t reader_thread, writer_thread;
    sem_init(&mutex, 0,1);
    sem_init(&wrt, 0, 1);
    sem_init(&order, 0, 0); //used for scheduling writer before reader


    for(int i = 0; i < 20; i++){
        pthread_create(&reader_thread, NULL, reader, (void *)(intptr_t)(i));
        pthread_create(&writer_thread, NULL, writer, NULL);
    }
    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&order);
}
