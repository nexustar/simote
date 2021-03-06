#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <SDL2/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "frame.h"
#include "decode.h"
#include "render.h"
#include "network.h"
#include "rtp.h"
#include "input.h"

int winw = 1280, winh = 720;
static int port_l, port_s;
static int s1, s2;
static char server_ip[50];
static void handle_arg(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	SDL_Thread *rtp_thread, *decode_thread, *render_thread;
	SDL_Event event;
	SDL_Window *win = NULL;

	handle_arg(argc, argv);
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("simote", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winw, winh, SDL_WINDOW_RESIZABLE);
	SDL_SetWindowGrab(win, SDL_TRUE);
	init_network(server_ip, port_s, port_l);
	s1 = init_decode();
	s2 = init_render(win, winw, winh);

	rtp_thread = SDL_CreateThread(rtp_loop, "simote_network", (void *)NULL);
	decode_thread = SDL_CreateThread(decode_loop, "simote_deocode", (void *)NULL);
	render_thread = SDL_CreateThread(render_loop, "simote_render", (void *)NULL);
	network_sendudp((uint8_t *)"svsb",4);

	while(SDL_WaitEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			SDL_Quit();
		case SDL_WINDOWEVENT:
			switch(event.window.event){
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				winw = event.window.data1;
				winh = event.window.data2;
			}
			break;
		case SDL_KEYDOWN:
			input_handle_keydown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			input_handle_keyup(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			input_handle_btndown(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			input_handle_btnup(event.button.button);
			break;
		case SDL_MOUSEMOTION:
			input_handle_mouse_moveto(event.motion.x, event.motion.y);
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
