//
//  20261_A5Server.c
//  Assignment5
//
//  Created by Xcode User on 2019-12-07.
//

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//constants
#define MAX 80 //message length
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buffer[MAX];
    int n;
    // chat loop
    for (;;) {
        bzero(buffer, MAX);

        read(sockfd, buffer, sizeof(buffer));
                
                //reads string for comparison to exit from client message
                if ((strncmp(buffer, "exit", 4)) == 0) {
            printf("Client Left - Server Now Exiting...\n");
            break;
        }
        // print which contains the client message
        printf("Here is the message: %sEnter the string: ", buffer);
        bzero(buffer, MAX);
                n = 0;
        // copy server message in the buffer
        while ((buffer[n++] = getchar()) != '\n')
            ;

        // return buffer to client
        write(sockfd, buffer, sizeof(buffer));
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // create socket and verify
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("failed to create socket...\n");
        exit(0);
    }
    else
        printf("created Socket successfully..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("connected...\n");

    // Chat Function
    func(connfd);

    // Close Socket
    close(sockfd);
}

