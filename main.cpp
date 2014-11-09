#include <iostream>
#include "communication_package/Tcp_client.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*if(argc < 3) {
        cout << "Missing arguments!" << endl;
        exit(EXIT_FAILURE);
    }*/
    int portNum = 8080;
    Tcp_client tcp_client(portNum, "localhost");
    tcp_client.connect_to_server();
    cout << "Connected to "<< argv[1] << " on port " << argv[2] << endl;
    char msg[] = "Hello From client!";
    tcp_client.send(msg, sizeof(msg));
    cout << "Server: " << (char*)tcp_client.receive() << endl;
    return 0;
}
