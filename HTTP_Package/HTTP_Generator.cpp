#include "HTTP_Generator.h"


HTTP_Generator::HTTP_Generator()
{

}

string HTTP_Generator::generate_get_request(string file_name ,string HTTP_type )
{

    string msg ("GET "+file_name+" "+HTTP_type+"\r\n");
    msg +="Host: "+get_host_name()+"\r\n";
    msg +="Accept: "+get_accepted_types()+"\r\n";
    msg +="Accept-Language: "+get_accepted_language()+"\r\n";
    msg +="User-Agent: "+get_user_agent()+"\r\n";

    return msg ;
}

string HTTP_Generator::generate_post_request(string file_name ,string HTTP_type , string file_type , char *data )
{
    string msg ("GET "+file_name+" "+HTTP_type+"\r\n");
    msg +="Host: "+get_host_name()+"\r\n";
    msg +="Accept: "+get_accepted_types()+"\r\n";
    msg +="Accept-Language: "+get_accepted_language()+"\r\n";
    msg +="User-Agent: "+get_user_agent()+"\r\n";
    msg +="Content-Type: "+file_type+"\r\n";
    cout << sizeof(data)<<endl;
    msg +="Content-Lenght: "+to_string(strlen(data)-1)+"\r\n\n";
    msg +=data;

    return msg ;
}


string HTTP_Generator::generate_get_response()
{

    string msg ("");

    return msg ;

}


string HTTP_Generator::generate_post_response()
{

    string msg ("");

    return msg ;

}

string HTTP_Generator::get_host_name ()
{

    ///TODO get hostname

    return ("MeGoFilio");
}

string HTTP_Generator::get_accepted_language ()
{

    ///TODO get accepted language from system

    return ("en-us , ar");
}

string HTTP_Generator::get_user_agent()
{

    /// TODO get user agent from system

    return ("Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)");
}

string HTTP_Generator::get_accepted_types()
{

    ///TODO get accepted files from system

    return ("*/*");

}

HTTP_Generator::~HTTP_Generator()
{
    //dtor
}