#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int msqid;
    struct msg_buffer message;
    __pid_t pid;

    msqid = msgget(IPC_PRIVATE, 0666|IPC_CREAT);

    pid = fork();

    if (pid == 0) {
        msgrcv(msqid, &message, sizeof(message), 1, 0); //function should receive a message with message type equal to 1.
        //the flag is set to 0 indicating that the function should block until a message is available.
        printf("Child received: %s\n", message.msg_text); 
    } else {
        printf("Enter message: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);
        message.msg_type = 1;
        msgsnd(msqid, &message, sizeof(message), 0); //the first available message type is used.
    }
    // to destroy the message queue 
    msgctl(msqid, IPC_RMID, NULL); 
    return 0;
}
