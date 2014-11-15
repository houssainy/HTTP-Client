#include "HTTP_client.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 3) {
        cout << "Missing arguments!" << endl;
        exit(EXIT_FAILURE);
    }

    HTTP_client httpClient(atoi(argv[2]), argv[1]);
    httpClient.connect();
    return 0;
}
