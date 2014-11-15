#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <netinet/in.h>
#include <netdb.h>
#include "../dynamic_array_package/Dynamic_array.h"

/**
* author Ahmed Abdelmajied
*
* Tcp_client class is implementation of TCP protocol in clients that's used to
* send and receive data from server and client and verse vise.
*/

using namespace std;
class Tcp_client
{
    public:
        // Constructor
        Tcp_client(int port_number,char* hostname);

        // Connect Method used to make client connect with server
        void connect_to_server();
        // Send method used to send data to server
        void send(const void* buf, int length);
        // Receive method used to receive data from server
        void receive(Dynamic_array *data);
        // close method used to close open connection with server
        void close_connection();
        // destructor
        virtual ~Tcp_client();
    private:
        int sockfd, portnum;
        struct sockaddr_in serv_addr;
        struct hostent *server;
};

#endif // TCP_CLIENT_H
