#include "HTTP_client.h"
#include "HTTP_Utils.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 3) {
        cout << "Missing arguments!" << endl;
        exit(EXIT_FAILURE);
    }

    HTTP_client httpClient(atoi(argv[2]), argv[1]);
    httpClient.start();
    unordered_map<string, char *> values;
    httpClient.execute(&values,HTTP_Utils::GET ,"/ip" , HTTP_Utils::HTTP1 , NULL);
    return 0;
}
