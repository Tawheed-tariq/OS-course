#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>

void forkExample();
void execExample();
void nmapScan(char *);
void whatweb(char *);
void execExample1();
void execveExample();
void execvpExample();
int main(){
    execExample1();
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
//execl
void execExample(){
    printf("the file fork-exec.c is running\n");
    __pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "cant fork process : %s\n", strerror(errno));
        exit(1);
    }
    if(pid == 0){
        printf("you are in child, the pid is %d\n", pid);
        if(execl("/usr/bin/python3", "python3", "exec.py", NULL) == -1){ //python3 exec.py
            fprintf(stderr, "cant run script : %s\n", strerror(errno)); 
        }
    }else{
        pid = wait(NULL);
        /*here the parent will not wait for child beacuse we are not using wait here*/
        printf("you are in parent, the pid of child is %d\n", pid);
        printf("the pid parent is %d\n", getpid());
    }  
}
//execle
void execExample1(){
    printf("running execle \n");
    __pid_t pid = fork();

    char *my_env[] = {"NAME=Tawheed","COLLEGE=NIT Srinagar", NULL};

    if(pid < 0){
        fprintf(stderr, "cant fork process : %s", strerror(errno));
    }
    else if(pid == 0){
        printf("child process created successfully \n");
        int status_code = execle("./envs", "./envs","running execle() system call", NULL, my_env);
        if(status_code == -1){
            printf("child process did not terminate correctly\n");
        }
    }
    else{
        pid = wait(NULL);
        printf("retruned to parent process\n");
    }
}
//execlp
void whatweb(char *target){
    printf("running whatweb scan on %s using exec system call\n", target);
    __pid_t pid = fork();


    if(pid < 0){
        fprintf(stderr, "cant fork process : %s", strerror(errno));
    }
    else if(pid == 0){
        printf("child process created successfully ");
        int status_code = execlp("whatweb", "whatweb", target, NULL);
        if(status_code == -1){
            printf("child process did not terminate correctly");
        }
    }
    else{
        pid = wait(NULL);
        printf("retruned to parent process");
    }
}
//execv
void nmapScan(char *target){
    printf("running nmap scan on %s using exec system call\n", target);
    __pid_t pid = fork();

    char *arg_list[] = {"nmap", "-sV", target, "-F", "-n", "-T5", NULL};

    if(pid < 0){
        fprintf(stderr, "cant fork process : %s", strerror(errno));
    }
    else if(pid == 0){
        printf("child process created successfully ");
        int status_code = execv("/bin/nmap", arg_list);
        if(status_code == -1){
            printf("child process did not terminate correctly");
        }
    }
    else{
        pid = wait(NULL);
        printf("retruned to parent process");
    }
}


void execvpExample(){
    __pid_t pid = fork();

    char *arg_list[] = {"python3","exec.py", NULL};
    if(pid < 0){
        fprintf(stderr, "cant fork process : %s", strerror(errno));
    }
    else if(pid == 0){
        printf("child process created successfully ");
        int status_code = execvp("python3", arg_list);
        if(status_code == -1){
            printf("child process did not terminate correctly");
        }
    }
    else{
        pid = wait(NULL);
        printf("retruned to parent process");
    }
}

void execveExample(){
    __pid_t pid = fork();

    char *arg_list[] = {"python3","exec.py", NULL};
    if(pid < 0){
        fprintf(stderr, "cant fork process : %s", strerror(errno));
    }
    else if(pid == 0){
        printf("child process created successfully ");
        int status_code = execve("/usr/bin/python3", arg_list, NULL);
        if(status_code == -1){
            printf("child process did not terminate correctly");
        }
    }
    else{
        pid = wait(NULL);
        printf("retruned to parent process");
    }
}