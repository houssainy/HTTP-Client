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
