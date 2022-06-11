#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
using namespace std;

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    int new_socket;
    int valread;
    int opt = 1;
    char buffer[1024] = {0};
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (server == 0) {
        cout << "Socket Failed";
        exit(EXIT_FAILURE);
    } 

    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        cout << "setsoockopt";
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(PORT);

    if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cout << "Bind Failed";
        exit(EXIT_FAILURE);
    }

    if (listen(server, 3) < 0) {
        cout << "Listen Error";
        exit(EXIT_FAILURE);
    }

    new_socket = accept(server, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (new_socket < 0) {
        cout << "Accept Error";
        exit(EXIT_FAILURE);
    }
}