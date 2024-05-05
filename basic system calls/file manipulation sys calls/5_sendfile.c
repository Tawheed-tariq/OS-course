#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/sendfile.h>

int main(void) 
{ 
    int fd[2];  
    off_t offset = 4;

    fd[0] = open("file.txt", O_WRONLY | O_CREAT, 0644); 
    fd[1] = open("start.txt", O_RDONLY | O_CREAT, 0644); 
  
    sendfile(fd[0], fd[1], &offset, 40); //starts from index == offset

    close(fd[0]); 
    close(fd[1]); 
  
    return 0; 
}