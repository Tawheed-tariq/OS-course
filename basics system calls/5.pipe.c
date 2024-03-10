#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

void error(char *msg){
    fprintf(stderr, "%s : %s\n", msg, strerror(errno));
    exit(1);
}

void open_url(char *url){
    char launch[200];
    sprintf(launch, "x-www-browser %s &", url);
    system(launch);
}

int main() {
    int fd[2];
    if(pipe(fd) == -1){
        error("cant create pipe");
    }
    pid_t pid = fork();

    if(pid == -1){
        error("cant create child process");
    }

    if(pid == 0){ 
        //you are in child

        dup2(fd[1], 1); //we replace the STDOUT with the file given to write pipe output to that file
        close(fd[0]); //child would not read the file so we close the read fd[0] file

        if(execl("/usr/bin/python", "/usr/bin/python", "./exec.py", NULL) == -1){
            error("cant run script");
        }
    }
    else {
        //you are in parent
        pid = wait(NULL);
        dup2(fd[0], 0); //we replace the STDIN with the file so that it reads from the file given
        close(fd[1]); //the parent will not write to file so we close it

        char line[200];

        while (fgets(line,200, stdin)){ //we can also use fd[0] in place of stdin
            if(line[0] == '\t'){
                open_url(line+1);
            }
        }
    }
}