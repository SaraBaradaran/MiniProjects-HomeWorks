#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SERVER_PORT 2777

int main(){

    char buff[255];
    int client_sock;
    struct sockaddr_in server_addr, client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    int num1, num2;
    printf("Enter the first number : ");
    scanf("%d", &num1);
    printf("Enter the second number :‌ ");
    scanf("%d", &num2);
    bzero(buff, sizeof(buff));
    sprintf(buff, "%d %d", num1, num2);

    int client_size = sizeof(client_addr);
    sendto(client_sock, (char *)buff, strlen(buff), MSG_CONFIRM, ( struct sockaddr*) &server_addr, sizeof(server_addr));
    bzero(buff, sizeof(buff));
    int server_size;
    int n = recvfrom(client_sock, (char *)buff, 254, MSG_WAITALL, ( struct sockaddr*) &server_addr, &server_size);
    buff[n] = '\0';

    printf("%s", buff);
    close(client_sock);

}
