#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <libavformat/avformat.h>
#include "receive.h"

static void add_nal_prefix(uint8_t *data);

int init_receive(int port)
{
	struct sockaddr_in serv_addr;
	int fd;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	return fd;
}

int receive_a_packet(int fd, AVPacket *packet)
{
	struct sockaddr caddr;
	socklen_t len = sizeof(caddr);
	uint8_t datagram[500][1600];
	uint8_t nalu_type;
	int rtplen[500];
	int i, j, n = 0, t = 0, s=0, size = 0;

	// reveive a rtp package and decide 
	rtplen[0] = recvfrom(fd, datagram[0], (size_t)1600, 0, &caddr, &len);
	nalu_type = datagram[0][12] & 0x1F;
	if (nalu_type == 0x01){
		av_new_packet(packet, rtplen[0] - 12 + 4);
		add_nal_prefix(packet->data);
		for(i = 12; i < rtplen[0]; i++)
			packet->data[i-8] = datagram[0][i];
		return 0;
	}
	else {
		n++;
		do{
			rtplen[n] = recvfrom(fd, datagram[n], (size_t)1600, 0, &caddr, &len);
			size += rtplen[n] - 12 - 2;
			n++;
		}while((datagram[n-1][1] & 0x80) != 0x80);
		// first bit means if it is the last datagram of a h264 packet
	}

	if(nalu_type == 0x18)
		size = (rtplen[0] + 3) + (n-2) * (rtplen[1] - 2) + rtplen[n-1] + 3;
	else if(nalu_type == 0x1C)
		size = (n-1) * (rtplen[0] - 2)  + rtplen[n-1] + 3;
	else
		printf("unknow type nalu type: %d\n", datagram[0][12] & 0x1F);
	av_new_packet(packet, size);

	if(nalu_type == 0x18){		
		add_nal_prefix(packet->data);
		for(t = 4, i = 15; i < 15 + datagram[0][13] * 0x1FF + datagram[0][14]; i++)
			packet->data[t++] = datagram[0][i];
		add_nal_prefix(packet->data+t);
		t += 4;
		for(i += 2; i < rtplen[0]; i++)
			packet->data[t++] = datagram[0][i];
		s = 1;
	}

	add_nal_prefix(packet->data+t);
	packet->data[t+4] = (datagram[1][12] & 0xE0) | (datagram[1][13] & 0x1F);
	t += 5;
	for (i = s; i < n; i++)
		for(j = 14; j < rtplen[i]; j++)
			packet->data[t++] = datagram[i][j];
	for(i = 1; i < n; i++)
		if(datagram[i][3] != datagram[i-1][3] + 1 && datagram[i][3] != 0x00)
			printf("boom!\n");
	return 0;
}

void exit_receive(int fd)
{
	close(fd);
}
static void add_nal_prefix(uint8_t *data)
{
	*data = 0x00;
	*(data+1) = 0x00;
	*(data+2) = 0x00;
	*(data+3) = 0x01;
}

