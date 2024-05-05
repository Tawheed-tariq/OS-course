#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(void) 
{ 
    int fd; 
    char buf1[40] = "Example text to write in test.txt";
  
    //opens the file.txt, if not created then also creates 
    fd = open("test.txt", O_WRONLY | O_CREAT, 0644); //write only
    
    pwrite(fd, buf1, strlen(buf1), 3); //writes the buf string from index 3 of file
  
    close(fd); 
    return 0; 
}