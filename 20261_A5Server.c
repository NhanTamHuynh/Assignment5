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
        bzero(buff, MAX);

        read(sockfd, buffer, sizeof(buff));
                
                //reads string for to compare for exit from client message
                if ((strncmp(buff, "exit", 4)) == 0) {
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


