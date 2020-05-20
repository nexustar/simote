#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <libavformat/avformat.h>
#include "frame.h"
#include "network.h"

#define BUF_NUM 10000

static uint8_t buf[BUF_NUM][1600];
static int buf_len[BUF_NUM], buf_f = 0, buf_r;

static int map(int x);
static void add_nal_prefix(uint8_t *data);

int rtp_loop(void *wtf)
{
	extern struct simote_now now;
	for(buf_r = 0; true; buf_r = (buf_r+1) % BUF_NUM){
		buf_len[buf_r] = network_getudp(buf[buf_r]);
		if((buf[buf_r][12] & 0x1F) == 0x01 || (buf[buf_r][1] & 0x80) == 0x80)
			SDL_SemPost(now.decode_sem);
	}
}

int receive_a_packet(AVPacket *packet)
{
	uint8_t nalu_type;
	int i, j, n = 0, t = 0, s=0, size = 0;

	// reveive a rtp package and decide which kind it is 
	nalu_type = buf[map(0)][12] & 0x1F;
	if (nalu_type == 0x01){
		av_new_packet(packet, buf_len[map(0)] - 12 + 4);
		add_nal_prefix(packet->data);
		for(i = 12; i < buf_len[map(0)]; i++)
			packet->data[i-8] = buf[map(0)][i];
		buf_len[map(0)] = 0;
		buf_f = map(1);
		return 0;
	}
	else {
		n++;
		do{
			n++;
		}while(buf_len[map(n-1)] > 0 && (buf[map(n-1)][1] & 0x80) != 0x80);
		// first bit means if it is the last datagram of a h264 packet
	}

	if(nalu_type == 0x18)
		size = (buf_len[map(0)] + 3) + (n-2) * (buf_len[map(1)] - 2) + buf_len[map(n-1)] + 3;
	else if(nalu_type == 0x1C)
		size = (n-1) * (buf_len[map(0)] - 2)  + buf_len[map(n-1)] + 3;
	else
		printf("unknow type nalu type: %d\n", nalu_type);
	av_new_packet(packet, size);

	if(nalu_type == 0x18){		
		add_nal_prefix(packet->data);
		for(t = 4, i = 15; i < 15 + buf[map(0)][13] * 0x1FF + buf[map(0)][14]; i++)
			packet->data[t++] = buf[map(0)][i];
		add_nal_prefix(packet->data+t);
		t += 4;
		for(i += 2; i < buf_len[map(0)]; i++)
			packet->data[t++] = buf[map(0)][i];
		s = 1;
	}

	add_nal_prefix(packet->data+t);
	packet->data[t+4] = (buf[map(1)][12] & 0xE0) | (buf[map(1)][13] & 0x1F);
	t += 5;
	for (i = s; i < n; i++){
		for(j = 14; j < buf_len[map(i)]; j++)
			packet->data[t++] = buf[map(i)][j];
		buf_len[map(i)] = 0;
	}
	for(i = 1; i < n; i++)
		if(buf[map(i)][3] != buf[map(i-1)][3] + 1 && buf[map(i)][3] != 0x00)
			printf("boom: %d %d %d %d\n", buf[map(i-2)][3], buf[map(i-1)][3], buf[map(i)][3], buf[map(i+1)][3]);
	buf_f = map(n);
	return 0;
}

static int map(int x)
{
	return (buf_f + x) % BUF_NUM;
}

static void add_nal_prefix(uint8_t *data)
{
	*data = 0x00;
	*(data+1) = 0x00;
	*(data+2) = 0x00;
	*(data+3) = 0x01;
}

