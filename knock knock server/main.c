#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<strings.h>

void error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int read_in(int socket, char *buf, int len){
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while(c > 0 && s[c-1] != '\n'){
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }

    if(c < 0) //error
        return c; 
    else if(c == 0) //client closed connection
        buf[0] = '\0';
    else //full string recieved successfully
        s[c-1] = '\0';
    return len-slen;
}

int open_listner_socket(){
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if(s == -1){
        error("can`t open socket");
    }

    return s;
}

void bind_to_port(int socket, int port){
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port); //name is internet port 30000
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    int reuse = 1;
    if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int))== -1){
        error("can`t set the reuse option on the socket");
    }

    int c = bind(socket, (struct sockaddr *) &name, sizeof(name)); //grab port 30000
    if(c == -1){
        error("cannot bind to socket");
    }
}

int say(int socket, char *msg){
    int result = send(socket, msg, strlen(msg), 0);
    if(result == -1){
        fprintf(stderr, "%s : %s\n", "error talking to client", strerror(errno));
    }
}

int listner_d;
void handle_shutdown(int sig){
    if(listner_d){
        close(listner_d);
    }

    fprintf(stderr, "Bye!\n");
    exit(0);
}

int main(){
    // if(catch_signal(SIGINT, handle_shutdown) == -1){
    //     error("cant set the interrupt handler"); //this will call handle_shutdown if ctrl-c is clicked 
    // }
    int listner_d = open_listner_socket();

    bind_to_port(listner_d, 30000); //create a socket on port 30000

    int listen_socket = listen(listner_d, 10); //set listen queue to length 10
    if(listen_socket == -1){
        error("can`t listen");
    }

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);

    puts("waiting for a connection\n");

    char buf[255];
    while(1){
        int connect_d = accept(listner_d, (struct sockaddr *) &client_addr, &address_size); //listen for a connection
        if(connect_d == -1){
            error("cannot open secondary socket");
        }

        char *msg = "Internet knock knock protocol server\r\nversion 1.0\r\nknock knock!\r\n";
        int res = say(connect_d, msg);
        if(res != -1){
            read_in(connect_d, buf, sizeof(buf)); //read data from client
            if(strncasecmp("who`s there!", buf, 12)){
                say(connect_d, buf);
                say(connect_d, "You Should say 'Who`s there!'\r\n"); //checking the user`s answers
            }
            else{
                if(say(connect_d, "Oscar\r\n") != -1){
                    read_in(connect_d, buf, sizeof(buf));
                    if(strncasecmp("Oscar who?", buf, 10))
                        say(connect_d, "You should say 'Oscar who?'\r\n");
                    else
                        say(connect_d, "Oscar silly question, you will get silly answer\r\n");
                } 
            }
        }
        close(connect_d);
    }
    return 0;
}