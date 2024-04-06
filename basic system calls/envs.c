//dinner_info
//connected with execle system call in 2.fork-exec.c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	printf("%s\n", argv[1]);
	printf("Name: %s\n", getenv("NAME"));
	printf("College: %s\n", getenv("COLLEGE"));
	return 0;
}