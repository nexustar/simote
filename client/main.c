#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <SDL2/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include "frame.h"
#include "decode.h"
#include "render.h"
#include "network.h"
#include "input.h"

static int winw = 1280, winh = 720;
static int port_l, port_s;
static int s1, s2;
static char server_ip[50];
static void handle_arg(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	SDL_Thread *decode_thread;
	SDL_Event event;

	handle_arg(argc, argv);
	printf("%s", server_ip);
	SDL_Init(SDL_INIT_VIDEO);
	init_network(server_ip, port_s, port_l);
	s1 = init_decode();
	s2 = init_render(winw, winh);

	decode_thread = SDL_CreateThread(decode_loop, "simote_deocode", (void *)NULL);
	network_sendudp((uint8_t *)"svsb",4);

	while(SDL_WaitEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			SDL_Quit();
		case SDL_WINDOWEVENT:
			switch(event.window.type){
			case SDL_WINDOWEVENT_RESIZED:
				;
			}
		case SDL_USEREVENT:
			render_a_frame();
			break;
		case SDL_KEYDOWN:
			input_handle_keydown(event.key.keysym.sym);
			break;
			printf("keydown");
		case SDL_KEYUP:
			input_handle_keyup(event.key.keysym.sym);
			printf("keyup %d\n", event.key.keysym.sym);
		case SDL_MOUSEMOTION:
			break;
		default :
			break;
		}
	}

	exit_network();
	SDL_Quit();
	return 0;
}

void handle_arg(int argc, char* argv[])
{
	char optc;
	extern char *optarg;
	extern int optind, opterr, optopt;

	while((optc = getopt(argc, argv, "s:p:l:h:w:")) != EOF){
		switch(optc){
		case 's':
			strcpy(server_ip, optarg);
			break;
		case 'p':
			port_s = atoi(optarg);
			break;
		case 'l':
			port_l = atoi(optarg);
			break;
		case 'h':
			winh = atoi(optarg);
			break;
		case 'w':
			winw = atoi(optarg);
			break;
		}
	}
	return;
}
