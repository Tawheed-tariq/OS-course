#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<stdint.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;


void *reader(void *arg){
    pthread_mutex_lock(&mutex);
    read_count++;
    if(read_count == 1)
        pthread_mutex_lock(&wrt); //if first reader then acquire lock so that no writer can access
    pthread_mutex_unlock(&mutex);

    int index = (intptr_t)arg;
    char buf[10];
    int fd = open("db.txt", O_RDONLY | O_CREAT, 0644);
    pread(fd, buf, 10, index*2); //reads from the index*2 index of file
    printf("reader {\n %s\n}\n\n", buf);

    pthread_mutex_lock(&mutex);
    read_count--;
    if(read_count == 0)
        pthread_mutex_unlock(&wrt); //if the last reader then release lock
    pthread_mutex_unlock(&mutex);
}

void *writer(){
    pthread_mutex_lock(&wrt);

    printf("writer ______________________\n\n");
    char buf[100] = "This is an example text been written in db.txt for representation of readers writers problem";
    int fd = open("db.txt", O_WRONLY | O_CREAT, 0644);
    write(fd, buf, strlen(buf));

    pthread_mutex_unlock(&wrt);
}

int main(){
    pthread_t reader_thread, writer_thread;

    for(int i = 0; i < 20; i++){
        pthread_create(&reader_thread, NULL, reader, (void *)(intptr_t)(i));
        pthread_create(&writer_thread, NULL, writer, NULL);
    }
    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);
}

/*
when initially the file is empty the reader will read nothing, so we have to schedule writer first.
We can do this ordering by using semaphores.
*/
