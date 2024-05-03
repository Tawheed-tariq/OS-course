#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(void) 
{ 
    int fd[2]; 
    char buf1[10] = "ExcEpt_mE!"; 
    char buf2[10]; 
  
    //opens the file.txt, if not created then also creates 
    fd[0] = open("file.txt", O_WRONLY | O_CREAT, 0644); //write only
    fd[1] = open("file.txt", O_RDONLY | O_CREAT, 0644); //read only
  
    write(fd[0], buf1, strlen(buf1)); 
    write(1, buf2, read(fd[1], buf2, 10)); //STDOUT has file no = 1 , therefore it write on STDOUT the read output of file.txt
  
    close(fd[0]); 
    close(fd[1]); 
  
    return 0; 
}