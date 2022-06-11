#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "wordle.h"
#define PORT 8080
using namespace std;

int main() {
    Wordle wordle = Wordle();
    struct sockaddr_in address;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int valread;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    if (sock < 0) {
        cout << "Socket Creation Error";
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) < 0) {
        cout << "Address not supported";
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Connection Failed";
        exit(EXIT_FAILURE);
    }

    wordle.start();
}