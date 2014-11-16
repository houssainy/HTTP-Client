#include "HTTP_client.h"

HTTP_client::HTTP_client(int portnum, char* hostname)
{
    //ctor
    HTTP_generator = new HTTP_Generator(hostname);

    this->portnum = portnum ;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "Can't open Socket!" << endl;
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        cout << "ERROR: no such host!" << endl;
        exit(EXIT_FAILURE);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);


}

void HTTP_client::start() {
    connect_to_server();


}

void HTTP_client::execute(unordered_map<string, char *> *values, string method_type, string file_path, string http_type, string file_type ) {
    if(method_type == HTTP_Utils::GET){
        // Send request
        string msg = HTTP_generator->generate_get_request(file_path, http_type);
        send(msg.c_str(),msg.size());

        // Receive response with data
        char buffer[256];
        Dynamic_array char_array ;
        int num_read = 0, offset = 0 ;
        bool data_flag = false, exit =false;
        ofstream out_stream;
        while (!exit && (num_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
            for (int i=0 ; i< num_read ; i++)
            {
                if (i>0 && buffer[i]=='\r' && char_array.get_at(i-1) == '\n' && !data_flag) {
                    i++;
                    HTTP_parser.parse_msg(values, char_array.get_array());
                    data_flag = true;
                    out_stream.open("text.txt");
                } else if (data_flag){
                    out_stream << buffer[i];
                    offset++;
                    if (offset == atoi(values->at(HTTP_Utils::CONTENT_LENGTH))){
                        exit = true;
                        out_stream.close();
                        break;
                    }
                    continue;
                }
                char_array.insert(buffer[i]);
            }
        }
    } else if (method_type == HTTP_Utils::POST){
        //read data
        Dynamic_array data ;
        ifstream is ("test.txt");
        char c;
        while(is.get(c))
            data.insert(c);

        // Send request
        string msg = HTTP_generator->generate_post_request(file_path,http_type,file_type,data.size());
        send(msg.c_str(), msg.size());
        // send data
        send(data.get_array(), data.size());

        //receive response
        char buffer[256];
        Dynamic_array char_array;
        int num_read = 0;
        bool exit =false;
        while (!exit && (num_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
            for (int i=0 ; i< num_read ; i++)
            {
                if (i>0 && buffer[i]=='\r' && char_array.get_at(i-1) == '\n' ) {
                    HTTP_parser.parse_msg(values, char_array.get_array());
                    exit = true;
                    break;
                }
                char_array.insert(buffer[i]);
            }
        }
    }


}

void HTTP_client::connect_to_server(){
    int n = connect(sockfd,(struct sockaddr *) &serv_addr,
                    sizeof(serv_addr));
    if (n < 0){
        cout<< "Can't connect to server " << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Connected to server on port " << this->portnum << endl;
}

void HTTP_client::send(const void* buf, int length)
{
    int n = write(sockfd, buf, length);
    if (n < 0)
        cout << "Error while sending data!" << endl;
}



void HTTP_client::close_connection()
{
    close(sockfd);
    cout << "Connection closed." << endl;
}

HTTP_client::~HTTP_client()
{
    //dtor
}
