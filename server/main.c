#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include "input.h"
#include "network.h"

static char width[10], height[10];
static void handle_arg(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	uint8_t data[1600];
	char ip[50], rtp_command[500];
	int port;

	handle_arg(argc, argv);
	init_uidev();
	init_network(8848);

	while(network_getudp(data, ip, &port) > 0){
		if(data[0] == 's' && data[1] == 'v')	//simote video
			if(data[2] == 's' && data[3] == 'b'){	//stream begin
				sprintf(rtp_command,"ffmpeg -device /dev/dri/card0 -f kmsgrab -framerate 60 -i - -vf 'hwmap=derive_device=vaapi,crop=%s:%s:0:0,scale_vaapi=w=%s:h=%s:format=nv12' -c:v h264_vaapi -qp 24 -bf 0 -f rtp rtp://%s:%d &", width, height, width, height, ip, port);
				system(rtp_command);
			}
		if(data[0] == 's' && data[1] == 'e'){	//simote even
			if(data[2] == 'k' && data[3] == 'd')	//key down
				send_key_down(to_linux_KEY(network_uint8to32(data+4)));
			if(data[2] == 'k' && data[3] == 'u')	//key up
				send_key_up(to_linux_KEY(network_uint8to32(data+4)));
		}
	}
	return 0;
}

void handle_arg(int argc, char* argv[])
{
	char optc;
	extern char *optarg;
	extern int optind, opterr, optopt;

	while((optc = getopt(argc, argv, "w:h:")) != EOF){
		switch(optc){
		case 'w':
			strcpy(width, optarg);
			break;
		case 'h':
			strcpy(height, optarg);
			break;
		}
	}
}
