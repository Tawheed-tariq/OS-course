#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
void error(char *);

int main(){
    FILE *fd = fopen("output.txt", "w");
    if(!fd){
        error("can't open file output.txt");
    }

    __pid_t pid = fork();

    if(pid == -1){
        error("can't fork process");
    }

    if(pid == 0){
        if(dup2(fileno(fd), 1) == -1){ /*here we redirected our STDOUT with file(output.txt)*/
            error("cannot duplicate file");
        }

        if(execl("/usr/bin/python3", "python3", "exec.py", NULL) == -1){
            error("cannot run script");
        }
    }else{
        pid = wait(NULL);
        printf("your child process ended with process ID %d\n", pid);
    }

    return 0;
}

void error(char *msg){
    fprintf(stderr, "%s : %s\n", msg, strerror(errno));
    exit(1);
}