#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libavformat/avformat.h>
#include "network.h"

static int fd;
static struct sockaddr_in serv_addr;
static struct sockaddr_in client_addr;

int init_network(char *ip, int ports, int portl)
{
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(ports);

	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_port = htons(portl);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, (struct sockaddr *)&client_addr, sizeof(client_addr));

	return 0;
}

int network_getudp(uint8_t *datagram)
{
	return recvfrom(fd, datagram, (size_t)1600, 0, NULL, NULL);
}

int network_sendudp(uint8_t *datagram, int len)
{
	return sendto(fd, datagram, len, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}

void exit_network(void)
{
	close(fd);
}

