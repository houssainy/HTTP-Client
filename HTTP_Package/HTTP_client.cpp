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

void HTTP_client::execute(string method_type, string file_path, string http_type  ) {
    if(method_type == HTTP_Utils::GET){
        // Get request life cycle
        // 1- send request without any data.
        // 2- receive response with data

        // Send request
        string msg = HTTP_generator->generate_get_request(file_path, http_type);
        send(msg.c_str(),msg.size());

        // Receive response with data
        char buffer[256];
        Dynamic_array char_array ;
        int num_read = 0, offset = 0 ;
        bool data_flag = false;
        ofstream out_stream;
        unordered_map <string, char *> values ;
        while ((num_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
            for (int i=0 ; i< num_read ; i++)
            {
                if (i>0 && buffer[i]=='\r' && buffer[i-1] == '\n' && !data_flag) {
                    i++;
                     HTTP_parser.parse_msg(&values, char_array.get_array());
                    data_flag = true;
                    out_stream.open("text.txt");
                } else if (data_flag){
                    out_stream << buffer[i];
                    offset++;
                    if (offset == atoi(values[HTTP_Utils::CONTENT_LENGTH]))
                        break;
                    continue;
                }
                char_array.insert(buffer[i]);
                cout<<buffer[i];
            }
        }
    } else if (method_type == HTTP_Utils::POST){
        //Post request life cycle:
        // 1- send request with data.
        // 2- receive respose without data.

        // Send request
        string msg = HTTP_generator->generate_get_request(file_path, http_type);
        send(msg.c_str(),msg.size());
        ///TODO read data
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

void HTTP_client::receive(Dynamic_array *data)
{
    char buffer[256];

    int num_read = 0;
    while ((num_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        for(int i = 0; i < num_read; i++)
            data->insert(buffer[i]);
    }
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
