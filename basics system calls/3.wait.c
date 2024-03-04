#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h>

void exampleWait(){
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
        /*in here we are using wait so the parent willl wait for the execution of child*/
        pid = wait(NULL);
        printf("you are in parent, the pid of child is %d\n", pid);
        printf("the pid parent is %d\n", getpid());
    }  

}

int main(){
    exampleWait();
    return 0;
}