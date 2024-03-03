#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>

void forkExample();
void execExample();


int main(){
    execExample();
    return 0;
    
}

void forkExample() {

    /*here we dont know whether operating system will give 1st priority to child or parent*/
    __pid_t p = fork();
    if (p < 0){
        perror("fork fail");
    }
    else if(p == 0){
        printf("hello from child\n");
    }
    else{
        printf("hello from parent\n");
    }
}

void execExample(){
    printf("the file fork-exec.c is running\n");
    __pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "cant fork process : %s\n", strerror(errno));
        exit(1);
    }
    if(pid == 0){
        printf("you are in child, the pid is %d\n", pid);
        if(execl("/usr/bin/python", "/usr/bin/python", "./exec.py", NULL) == -1){
            fprintf(stderr, "cant run script : %s\n", strerror(errno)); 
        }
    }else{

        /*here the parent will not wait for child beacuse we are not using wait here*/
        printf("you are in parent, the pid of child is %d\n", pid);
        printf("the pid parent is %d\n", getpid());
    }  
}