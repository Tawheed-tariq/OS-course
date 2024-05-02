#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

/*pipe is used to open file descriptors ,which are used to communicate between processes*/

void error(char *msg){
    fprintf(stderr, "%s : %s\n", msg, strerror(errno));
    exit(1);
}

void open_url(char *url){
    char launch[200];
    sprintf(launch, "x-www-browser '%s' &", url);
    system(launch);
}

int main() {
    int fd[2];
    char buffer[100];
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

        read(fd[0], buffer, 100);
        printf("%s", buffer);
        open_url(buffer); //will open the browser and link which is written in exec.py
    }
}