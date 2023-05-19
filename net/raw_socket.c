#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 65536

int main() {
    int sockfd;
    struct sockaddr_in my_addr, their_addr;
    unsigned char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(struct sockaddr);

    // Create a raw socket that receives all IP packets
    if (sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a specific interface
    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_PACKET;
    my_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Listening...\n");
    
    while (1) {
        // Receive a packet
        int numbytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&their_addr, &addr_len);
        printf("Received a packet of %d bytes\n", numbytes);

        // Print the packet contents as hex
        for (int i = 0; i < numbytes; i++) {
            printf("%02x ", buffer[i]);
            if ((i + 1) % 16 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }

    // Close the socket
    close(sockfd);
    return 0;
}

