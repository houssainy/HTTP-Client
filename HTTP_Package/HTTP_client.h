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
#include <unordered_map>

#include <iostream>
#include "../dynamic_array_package/Dynamic_array.h"

#include "HTTP_Generator.h"
#include "HTTP_Parser.h"
#include "HTTP_Utils.h"

using namespace std;

/**
* This class is an ipmlementation for a simple HTTP Client.
*
* Using HTTP_client you can send GET request and POST request.
*/
class HTTP_client {
  public:
    HTTP_client(int portNumber, char* host);
    void start();
    bool execute(string method_type, string file_path, string http_type);
    void close_connection();
    virtual ~HTTP_client();
  private:
    int sockfd, portnum;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    HTTP_Generator *HTTP_generator;
    HTTP_Parser HTTP_parser;

    void connect_to_server();
    void send(const void* buf, int length);

    void exectue_get_request(string file_path, string http_type);
    void exectue_post_request(string file_path, string http_type);

    string get_file_type(string file_path);
    string get_file_name(string file_path);
};

#endif // HTTP_CLIENT_H
