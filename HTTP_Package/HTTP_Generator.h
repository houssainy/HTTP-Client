#ifndef HTTP_GENERATOR_H
#define HTTP_GENERATOR_H
#include <string>


using namespace std ;
class HTTP_Generator
{
    public:
        static const unsigned char HTTP1 = 1;
        static const unsigned char HTTP2 = 2;

        HTTP_Generator();
        void generate_get_request(string file_name ,unsigned char HTTP_type );
        virtual ~HTTP_Generator();
    protected:
    private:
};

#endif // HTTP_GENERATOR_H
