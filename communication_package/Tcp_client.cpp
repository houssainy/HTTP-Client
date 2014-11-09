#include "Tcp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

using namespace std;
Tcp_client::Tcp_client(int port_number, char* hostname){
    this->portnum = port_number ;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "Can't open Socket!" << endl;
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        cout << "ERROR: no such host!" << endl;
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
    int n = connect(sockfd,(struct sockaddr *) &serv_addr,
                    sizeof(serv_addr));
    if (n < 0){
        cout<< "Can't connect to server " << endl;
        exit(EXIT_FAILURE);
    }
}

void Tcp_client::send(const void* buf, int length){
    int n = write(sockfd, buf, length);
    if (n < 0)
        printf("can't write in socket");
}

void* Tcp_client::receive(){
    unsigned char buffer[256];
    bzero(buffer, 256);
    int n = read(sockfd, buffer, 255);
    if (n < 0) {
        printf("can't read in socket");
        return NULL;
    }
    return buffer;
}

void Tcp_client::close_connection(){
    close(sockfd);
}


Tcp_client::~Tcp_client()
{
    //dtor
}
