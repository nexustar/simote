#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<SDL2/SDL.h>
#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<libswscale/swscale.h>
#include"frame.h"
#include"decode.h"
#include"render.h"
#include"receive.h"

static int winw = 1280, winh = 720;
static int port_l, port_s;
static int rtp_fd, s1, s2;
static void handle_arg(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	SDL_Thread *decode_thread;
	SDL_Thread *render_thread;
	SDL_Event event;

	handle_arg(argc, argv);
	SDL_Init(SDL_INIT_VIDEO);
	rtp_fd = init_receive(port_l);
	s1 = init_decode(rtp_fd);
	s2 = init_render(winw, winh);

	decode_thread = SDL_CreateThread(decode_loop, "simote_deocode", (void *)NULL);

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
		case SDL_MOUSEMOTION:
			break;
		default :
			break;
		}
	}

	exit_receive(rtp_fd);
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
			break;
		case 'p':
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
