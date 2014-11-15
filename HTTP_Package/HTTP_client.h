#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <fstream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>
#include "../dynamic_array_package/Dynamic_array.h"

#include "HTTP_Generator.h"
#include "HTTP_Parser.h"
#include "HTTP_Utils.h"

using namespace std;

class HTTP_client
{
    public:
        HTTP_client(int portNumber, char* host);
        void start();
        void execute(string method_type, string file_path, string http_type);
        virtual ~HTTP_client();
    private:
        int sockfd, portnum;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        HTTP_Generator HTTP_generator;
        // Connect Method used to make client connect with server
        void connect_to_server();
        // Send method used to send data to server
        void send(const void* buf, int length);
        // Receive method used to receive data from server
        void receive(Dynamic_array *data);
        // close method used to close open connection with server
        void close_connection();
};

#endif // HTTP_CLIENT_H
