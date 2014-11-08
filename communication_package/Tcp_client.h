#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <netinet/in.h>
#include <netdb.h>

/**
* author Ahmed Abdelmajied
*
* Tcp_client class is implementation of TCP protocol in clients that's used to
* send and receive data from server and client and verse vise.
*/

class Tcp_client
{
public:
    // Constructor
    Tcp_client(int port_number,char* hostname);
    // Connect Method used to make client connect with server
    void connect_to_server();
    // Send method used to send data to server
    void send(void *data);
    // Receive method used to receive data from server
    void* receive();
    // close method used to close open connection with server
    void close_connection();
    // deconstructor
    virtual ~Tcp_client();
protected:

private:
 int sockfd , portnum , check ;
 struct sockaddr_in serv_addr;
 struct hostent *server;
};

#endif // TCP_CLIENT_H
