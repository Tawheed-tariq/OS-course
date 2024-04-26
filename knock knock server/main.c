#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<errno.h>

void error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(){
    char *advice[] = {
        "Take smaller bites\r\n",
        "Go for the tight jeans. No they do NOT make you look fat.\r\n",
        "One word: inappropriate\r\n",
        "Just for today, be honest. Tell your boss what you *really* think\r\n",
        "You might want to rethink that haircut\r\n"
    };

    int listner_d = socket(PF_INET, SOCK_STREAM, 0);
    if(listner_d == -1){
        error("can`t open socket");
    }

    int reuse = 1;
    if(setsockopt(listner_d, SOL_SOCKET, SO_REUSEADDR, (char *)reuse, sizeof(int))== -1){
        error("can`t set the reuse option on the socket");
    }

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int c = bind(listner_d, (struct sockaddr *) &name, sizeof(name));
    if(c == -1){
        error("cannot bind to socket");
    }


    int listen_socket = listen(listner_d, 10);
    if(listen_socket == -1){
        error("can`t listen");
    }
    puts("waiting for a connection\n");

    while(1){
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listner_d, (struct sockaddr *) &client_addr, &address_size);
        if(connect_d == -1){
            error("cannot open secondary socket");
        }
        char *msg = advice[rand() % 5];

        send(connect_d, msg, strlen(msg), 0);
        close(connect_d);
    }

    return 0;
}