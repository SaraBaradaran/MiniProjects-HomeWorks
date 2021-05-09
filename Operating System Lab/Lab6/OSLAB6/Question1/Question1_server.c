#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SERVER_PORT 2777
#define MAX_CLIENT 5

int main(){

    char buff[255];
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(server_sock, (struct sockaddr*) & server_addr, sizeof(server_addr));
    listen(server_sock, MAX_CLIENT);

    while(1){
        int client_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*) & server_addr, &(client_size));
        if(client_sock >= 0)
            printf("Connection established successfully\n");
        else{
            printf("Connection failed\n");
            continue;
        }
        
        bzero(buff, sizeof(buff));
        read(client_sock, buff, sizeof(buff));

        char* filename = (char*) malloc(strlen(buff) * sizeof(char));
        strcpy(filename, buff);
        
        FILE* file = fopen(filename, "r");
        if(!file){
            printf("file clould not been opened\n");
            continue;
        }
        while (fgets(buff, sizeof(buff) , file))
        {
            write(client_sock, buff, strlen(buff));
            bzero(buff, sizeof(buff));
        }
        close(client_sock);
    }
}
