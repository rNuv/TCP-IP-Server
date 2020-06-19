#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    //create server socket
    int server_socket; 
    server_socket = socket(AF_INET, SOCK_STREAM, 0); 

    //define server address
    struct sockaddr_in server_address; 
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9003);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    //bind the socket to the address
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //listen for connections to socket
    listen(server_socket, 3);

    //accept the client socket
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    char client_message[256];
    char server_response[256] = "Status: Received";
    
    recv(client_socket, &client_message, sizeof(client_message), 0);
    printf("Message Received: %s\n", client_message);
    while(strcmp(client_message, "exit") != 0){
        send(client_socket, server_response, sizeof(server_response), 0);
        recv(client_socket, &client_message, sizeof(client_message), 0);
        printf("Message Received: %s\n", client_message);
    }

    close(server_socket);
    
    return 0;
}