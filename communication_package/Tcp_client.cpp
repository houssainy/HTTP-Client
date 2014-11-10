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
    // Send size of data
    char data_size[4];
    int arraySize = length;
    // convert arraySize to byte array
    for (int i = 0; i < 4; i++) {
        data_size[i] = (char) (arraySize & 0xff);
        arraySize >>= 8;
    }
    int n = write(sockfd, data_size, 4);
    if (n < 0)
        cout << "Error while sending data!" << endl;
    // Send data
    n = write(sockfd, buf, length);
    if (n < 0)
        cout << "Error while sending data!" << endl;
}

char* Tcp_client::receive(){
    // Receive size
    char temp[4];

    int n = read(sockfd, temp, 4);
    if (n < 0)
        cout << "ERROR in reading from data!" << endl;

	// convert received size from byte array to integer
    int data_lenght = 0;
    for (int i = 4- 1; i >= 0; i--) {
        data_lenght |= (temp[i] & 0xff);
        if (i != 0)
            data_lenght  <<= 8;
    }
    // Receive data
    char *data = new char[data_lenght];
    int offset = 0;
    int num_read = 0;
    while (offset < data_lenght
            && (num_read = read(sockfd, data, data_lenght)) >= 0) {
        offset += num_read;
    }

    if (offset < data_lenght) {
        cout << "ERROR: Can't receive all the data!" << endl;
        return NULL;
    }
    return data;
}

void Tcp_client::close_connection(){
    close(sockfd);
    cout << "Connection closed." << endl;
}


Tcp_client::~Tcp_client()
{
    //dtor
}

