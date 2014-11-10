#ifndef HTTP_GENERATOR_H
#define HTTP_GENERATOR_H
#include <string>
#include <string.h>
#include <iostream>

using namespace std ;
class HTTP_Generator
{
    public:

        const static string HTTP1 ;
        const static string HTTP2 ;
        const static string image ;
        const static string txt   ;

        HTTP_Generator();
        string generate_get_request (string file_name ,string HTTP_type );
        string generate_post_request(string file_name ,string HTTP_type , string file_type , char *data );

        string generate_get_response();
        string generate_post_response();
        virtual ~HTTP_Generator();


    private:
        string get_host_name ();
        string get_accepted_language ();
        string get_user_agent();
        string get_accepted_types();
};


#endif // HTTP_GENERATOR_H