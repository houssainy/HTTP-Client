#include <iostream>
#include "communication_package/Tcp_client.h"

#include <fstream>
#include <string>
#include "HTTP_Package/HTTP_Generator.h"

const string HTTP_Generator::HTTP1 = "HTTP/1.0" ;
const string HTTP_Generator::HTTP2 = "HTTP/1.1" ;
const string HTTP_Generator::image = "image/*"  ;
const string HTTP_Generator::txt   = "text/html";
using namespace std;

int main(int argc, char *argv[])
{
/*
    if(argc < 3) {
        cout << "Missing arguments!" << endl;
        exit(EXIT_FAILURE);
    }
    int portNum = atoi(argv[2]);
    Tcp_client tcp_client(portNum, argv[1]);
    tcp_client.connect_to_server();
    cout << "Connected to "<< argv[1] << " on port " << argv[2] << endl;
    char msg[] = "Hello From client!";
    tcp_client.send(msg, sizeof(msg));
    cout << "Server: " << (char*)tcp_client.receive() << endl;
    return 0;
*/
    HTTP_Generator gen ;
    ifstream inFile;
	size_t size = 0;
	inFile.open("test.txt", ios::in|ios::binary|ios::ate);

    char* data = 0;

	if(inFile.is_open()) {


		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		data = new char[size+1];
		inFile.read(data, size);
		data[size] = '\0';
	}

    string msg = gen.generate_post_request("Ahmed",HTTP_Generator::HTTP2,HTTP_Generator::txt , data);
    cout << msg <<endl;

}
