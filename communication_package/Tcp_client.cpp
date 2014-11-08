#include "Tcp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

Tcp_client::Tcp_client(int port_number,char* hostname){

}

void Tcp_client::connect(){
}


void Tcp_client::send(void *data){

}

void* Tcp_client::receive(){

return 0;
}

void Tcp_client::close(){

}
Tcp_client::~Tcp_client()
{
    //dtor
}
