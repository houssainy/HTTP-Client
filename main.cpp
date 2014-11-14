#include <iostream>
#include "communication_package/Tcp_client.h"

#include <fstream>
#include <string>
#include "HTTP_Package/HTTP_Generator.h"
#include "HTTP_Package/HTTP_Parser.h"
#include "HTTP_Package/HTTP_Utils.h"



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

    string msg = gen.generate_get_response(HTTP_Utils::HTTP2,HTTP_Utils::OK , "text/*",data);
    cout << msg <<endl;

    HTTP_Parser par ;
    par.parse_msg(msg);

    msg  = gen.generate_get_request("Ahmed",HTTP_Utils::HTTP1);
    cout << msg <<endl;
    par.parse_msg(msg);


}
