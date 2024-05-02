#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(){
    printf("You pressed 'ctrl + c'\n");
}

void sigquit_handler(){
    printf("you pressed 'ctrl+ \\'\n");
    printf("now exiting the program");
    exit(0);
}

int main(){
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    for (int i=1;; ++i) {
        printf("%d: give a signal\n", i);
        sleep(1);
    }
    return 0;
}