//program to take input from STDIN and store in output.txt
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(){
    int fd;
    char buf[2000];
    char buf2[] = "Write the text you want to get stored in file:\n";
    fd = open("output.txt", O_RDWR | O_CREAT, 0644);

    write(1, buf2, strlen(buf2));//write on STDOUT
    read(0, buf, 2000); //read from STDIN
    write(fd, buf, strlen(buf)); //write to file
    close(fd);
    return 0;
}