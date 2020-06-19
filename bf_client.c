#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){

    //create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9003);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if(connection_status == -1)
        printf("Connection Error");

    char client_message[256];
    char server_response[256];
    while(strcmp(client_message, "exit") != 0){
        printf("Enter Message: ");
        scanf("%s", client_message);
        send(network_socket, client_message, sizeof(client_message), 0);
        recv(network_socket, &server_response, sizeof(server_response), 0);
        printf("%s\n", server_response);
    }

    close(network_socket);

    return 0;
}