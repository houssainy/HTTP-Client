#include "Tcp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


Tcp_client::Tcp_client(int port_number,char* hostname){

    portnum = portnum ;
    sockfd= socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        printf("Can't open Socket");
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);

}

void Tcp_client::connect_to_server(){

    int test = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if (test < 0){
        printf ("Can't connect to server ");
        exit(EXIT_FAILURE);
    }

}


void Tcp_client::send(void *data){

    check = write(sockfd,data, sizeof(data));
    if (check<0)
        printf("can't write in socket");
}

void* Tcp_client::receive(){
    void * data ;
    bzero(data,sizeof(data));
    check = read(sockfd,data,21);
        if (check<0)
            printf("can't read in socket");
            return NULL;
    return data;
}

void Tcp_client::close_connection(){
    close(sockfd);
}


Tcp_client::~Tcp_client()
{
    //dtor
}
