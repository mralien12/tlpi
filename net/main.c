#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <string.h>

int main() {
	struct sockaddr_ll addr;
	struct ethhdr *frameHeader;
	int fd;
	unsigned char buffer[1500];

	fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fd < 0) {
		perror("socket failed\n");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	/* addr.sll_ifindex = */ 
	addr.sll_family = AF_PACKET;
	addr.sll_protocol = htons(ETH_P_ALL);
	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr))) {
		perror("bind failed\n");
		goto close;
	}

	printf("Listening...\n");

	while (1) {
		int numbytes = recvfrom(fd, buffer, sizeof(buffer), 0, NULL, NULL);
		frameHeader = (struct ethhdr *) buffer;
		printf("Type: %04x ", ntohs(frameHeader->h_proto));
		/* for (int i = 0; i < 6; i++) { */
		/* 	printf("%02x ", buffer[i]); */
		/* } */
		/* printf(" -> "); */
		/* for (int i = 6; i < 12; i++) { */
		/* 	printf("%02x ", buffer[i]); */
		/* } */
		/* printf("TYPE: "); */
		/* for (int i = 12; i < 14; i++) { */
		/* 	printf("%02x ", buffer[i]); */
		/* } */
		printf("received %d bytes\n", numbytes);
	}

close:
	close(fd);
	return 0;
}
