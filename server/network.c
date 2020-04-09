#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <libavformat/avformat.h>
#include "network.h"

static int fd;
static struct sockaddr_in serv_addr;
static socklen_t len;

int init_network(int port)
{
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	len = sizeof(struct sockaddr);

	return 0;
}

int network_getudp(uint8_t *datagram)
{
	struct sockaddr caddr;
	return recvfrom(fd, datagram, (size_t)1600, 0, &caddr, &len);
}


void exit_network(void)
{
	close(fd);
}

uint32_t network_uint8to32(uint8_t* data)
{
	return (data[0]<<24) | (data[1]<<16) | (data[2]<<8) | (data[3]);
}
