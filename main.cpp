#include "HTTP_client.h"
#include "HTTP_Utils.h"

using namespace std;

int main(int argc, char *argv[]) {
  if(argc < 3) {
      cout << "Missing arguments!" << endl;
      exit(EXIT_FAILURE);
  }

  HTTP_client httpClient(atoi(argv[2]), argv[1]);
  httpClient.start();

  string input;
  cin >> input;
  do {
    httpClient.execute(HTTP_Utils::GET ,"ahmed" , HTTP_Utils::HTTP1);
  } while(input != "exit");

  httpClient.close_connection();
  return 0;
}
