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
    int server_sock;
    struct sockaddr_in server_addr, client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    int bind_res = bind(server_sock, (const struct sockaddr*) & server_addr, sizeof(server_addr));
    if(bind_res < 0){
        printf("bind faild\n");
        return 0;
    }
    while(1){
        
        int client_size = sizeof(client_addr);
        int n = recvfrom(server_sock, (char *)buff, 254, MSG_WAITALL, ( struct sockaddr*) &client_addr, &client_size);
        buff[n] = '\0';

        char num1[5], num2[5];
        for(int i=0; i<strlen(buff); i++){
            if(buff[i] == ' '){
                num1[i] = '\0';
                int j;
                for(j=i+1; j<strlen(buff); j++){
                    num2[j - (i+1)] = buff[j];
                }
                num2[j - (i+1)] = '\0';
                break;
            }
            num1[i] = buff[i];
            
        }
        
        int res = atoi(num1) + atoi(num2);
        bzero(buff, sizeof(buff));
        sprintf(buff, "%d", res);
        sendto(server_sock, (char *)buff, strlen(buff), MSG_CONFIRM, ( struct sockaddr*) &client_addr, client_size);
    }
    close(server_sock);

}
