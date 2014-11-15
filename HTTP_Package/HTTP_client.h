#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <iostream>
#include "../communication_package/Tcp_client.h"
#include "../dynamic_array_package/Dynamic_array.h"
#include "HTTP_Generator.h"
#include "HTTP_Parser.h"

#include <fstream>
#include <string>

using namespace std;

class HTTP_client
{
    public:
        HTTP_client(int portNumber, char* host);
        void connect();
        virtual ~HTTP_client();
    private:
        Tcp_client *tcp_client;
        HTTP_Generator HTTP_generator ;
};

#endif // HTTP_CLIENT_H
