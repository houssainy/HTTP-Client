#include <iostream>
#include "communication_package/Tcp_client.h"

#include <fstream>
#include <string>
#include "HTTP_Package/HTTP_Generator.h"
#include "HTTP_Package/HTTP_Parser.h"



const string HTTP_Generator::HTTP1      = "HTTP/1.0" ;
const string HTTP_Generator::HTTP2      = "HTTP/1.1" ;
const string HTTP_Generator::image      = "image/*"  ;
const string HTTP_Generator::txt        = "text/html";
const string HTTP_Generator::ok         = "200 OK"   ;
const string HTTP_Generator::not_found  = "404 Not Found";

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


    string msg = gen.generate_get_request("Ahmed",HTTP_Generator::HTTP1);
    cout << msg <<endl;
//    cout << msg.substr(20,15)<<endl;
    HTTP_Parser par ;
    par.parse_request(msg);
}
