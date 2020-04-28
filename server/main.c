#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include "input.h"
#include "network.h"

static int orgin_w, orgin_h, width, height, crtc_id = 0, abs_w, abs_h, abs_x, abs_y;
static char scale[50] = "";
static void handle_arg(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	uint8_t data[1600];
	char ip[50], rtp_command[500];
	int port;

	handle_arg(argc, argv);
	printf("ok\n");
	init_uidev(abs_w, abs_h, abs_x, abs_y);
	init_network(8848);

	while(network_getudp(data, ip, &port) > 0){
		if(data[0] == 's' && data[1] == 'v')	//simote video
			if(data[2] == 's' && data[3] == 'b'){	//stream begin
				sprintf(rtp_command,"ffmpeg -device /dev/dri/card0 -f kmsgrab -crtc_id %d -framerate 60 -i - -vf 'hwmap=derive_device=vaapi,scale_vaapi=%sformat=nv12' -c:v h264_vaapi -qp 24 -bf 0 -f rtp rtp://%s:%d &", crtc_id, scale, ip, port);
				system(rtp_command);
			}
		if(data[0] == 's' && data[1] == 'e'){	//simote even
			if(data[2] == 'k' && data[3] == 'd')	//key down
				send_key_down(to_linux_KEY(network_uint8to32(data+4)));
			if(data[2] == 'k' && data[3] == 'u')	//key up
				send_key_up(to_linux_KEY(network_uint8to32(data+4)));
			if(data[2] == 'm' && data[3] == 'a')	//mouse absolute move
				send_mouse_moveto((data[4]<<8 | data[5]) * orgin_w / width / 4, (data[6]<<8 | data[7]) * orgin_h / height / 4);
		}
	}
	return 0;
}

void handle_arg(int argc, char* argv[])
{
	char optc;
	extern char *optarg;
	extern int optind, opterr, optopt;

	while((optc = getopt(argc, argv, "c:S:s:a:")) != EOF){
		switch(optc){
		case 'c':
			crtc_id = atoi(optarg);
			break;
		case 'S':
			sscanf(optarg, "%d:%d", &orgin_w, &orgin_h);
			printf("%d %d\n", orgin_w, orgin_h);
			break;
		case 's':
			sscanf(optarg, "%d:%d", &width, &height);
			sprintf(scale, "w=%d:h=%d:", width, height);
			printf("%s\n", scale);
			break;
		case 'a':
			sscanf(optarg, "%d:%d:%d:%d", &abs_w, &abs_h, &abs_x, &abs_y);
			printf("%d %d %d %d\n", abs_h, abs_w, abs_x, abs_y);
			break;
		}
	}
}
