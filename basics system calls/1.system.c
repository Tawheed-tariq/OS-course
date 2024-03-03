/* system() takes a single string parameter and executes it
 as if you had typed it on the command line:*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

char* now(){
    time_t t;
    time(&t);
    return asctime(localtime(&t));
}

int main(){
    // system("ls ~/tawheed/Documents/Programming"); //prints all the directories present in the given location
    
    char comment[80];
    char cmd[120];

    printf("write some string\n");
    fgets(comment, 80, stdin); /*using fgets for unstructured text , it needs to store text in comment array,
                                there is room for only 80 characters , the input will be taken from keyboard(stdin) */

    sprintf(cmd, "echo '%s %s' > report.log", comment, now()); /*sprintf() will print the characters to a stirng , 
                                                                the formatted string will be storen in cmd array*/
    /*echo is a built-in Linux command that is used to display the text passed in as an argument*/

    system(cmd); //this runs the content of cmd
    return 0;
}

