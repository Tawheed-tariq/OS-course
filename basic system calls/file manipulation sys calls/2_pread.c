#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(void) 
{ 
    int fd; 
    char buf1[20];
  
    //opens the file.txt, if not created then also creates 
    fd = open("test.txt", O_RDONLY | O_CREAT, 0644); //write only
    
    ssize_t count = pread(fd, buf1, 20, 5); //will start reading from index 5 in test.txt
    write(1, buf1, count); 
  
    close(fd); 
  
    return 0; 
}