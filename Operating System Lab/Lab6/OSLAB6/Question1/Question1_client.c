#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 2777

int main(){

    char buff[255];
    int client_sock;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int connection = connect(client_sock, (struct sockaddr*) & server_addr, sizeof(server_addr));
    
    if(connection == 0)
        printf("Connection established successfully\n");
        
    else{
        printf("Connection failed\n");
        return 0;
    }

    bzero(buff, sizeof(buff));
    printf("Enter the name of file you want to send to server : ");
    scanf("%s", buff);
    write(client_sock, buff, strlen(buff));
    
    FILE* file = fopen("client_cpy.txt", "w");
    if(!file){
        printf("file clould not been opened\n");
        return 0;
    }
    bzero(buff, sizeof(buff));
    while (read(client_sock, buff, sizeof(buff)))
    {
        fprintf(file, "%s", buff);
        bzero(buff, sizeof(buff));

    }
    fclose(file);
    close(client_sock);
}
