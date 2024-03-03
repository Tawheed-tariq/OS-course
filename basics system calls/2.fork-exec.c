#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(){
    printf("the file fork-exec.c is running\n");
    __pid_t pid = fork();

    if(pid == 0){
        printf("you are in child process now");
    }else{
        printf("pid value is %d\n", pid);
    }

    if(pid == -1){
        fprintf(stderr, "cant fork process : %s\n", strerror(errno));
        return 1;
    }
    if(!pid){
        int result = execl("/usr/bin/python", "/usr/bin/python", "./exec.py", NULL);
        if(result == -1){
            fprintf(stderr, "cant run script : %s\n", strerror(errno)); 
        }
        return 1;
    }

    
}