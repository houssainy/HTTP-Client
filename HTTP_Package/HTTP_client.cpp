#include "HTTP_client.h"

HTTP_client::HTTP_client(int portNumber, char* host)
{
    //ctor
    tcp_client = new Tcp_client(portNumber, host);
}

void HTTP_client::connect() {
    tcp_client->connect_to_server();

    // TODO(houssainy)
    char msg[] = "Hello From client!";
    tcp_client->send(msg, sizeof(msg));

    char * z = tcp_client->receive();
    cout<< "Received: " << z << endl;

    // Receive file
    // Receive size
    ofstream outfile;
    outfile.open("example.jpg");
    string line = "";
    while((line = tcp_client->receive()) != "\0") {
        outfile << line << endl;
    }

    outfile.close();
    tcp_client->close_connection();
}

HTTP_client::~HTTP_client()
{
    //dtor
}
