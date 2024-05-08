// It creates a shared memory segment, writes to it from the parent process, 
//and reads from it in the child process.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/wait.h>
int main() {
    int shmid;
    char *shared_memory;
    __pid_t pid;

    shmid = shmget(IPC_PRIVATE, 20*sizeof(char), 0666|IPC_CREAT);

    pid = fork();

    if (pid == 0) {
        // Child process
        shared_memory = shmat(shmid, NULL, 0);
        printf("Child process: %s\n", shared_memory);
        shmdt(shared_memory);
    } else {
        // Parent process
        shared_memory = shmat(shmid, NULL, 0);
        sprintf(shared_memory, "Hello from parent!");
        wait(NULL);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
