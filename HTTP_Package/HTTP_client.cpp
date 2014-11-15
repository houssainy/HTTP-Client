#include "HTTP_client.h"

HTTP_client::HTTP_client(int portNumber, char* host)
{
    //ctor
    tcp_client = new Tcp_client(portNumber, host);
}

void HTTP_client::connect() {
    tcp_client->connect_to_server();

    // TODO(houssainy)

    string msg = HTTP_generator.generate_get_request("/ip" ,HTTP_Utils::HTTP1);
    tcp_client->send(msg.c_str() , msg.size());

    Dynamic_array data;
    tcp_client->receive(&data);
    for(int i = 0; i < data.size(); i++) {
        cout<< data.get_at(i);
    }
    cout << endl;
}

HTTP_client::~HTTP_client()
{
    //dtor
    tcp_client->close_connection();
    delete tcp_client;
}
