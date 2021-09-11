#include <stdio.h>
#include <SDL2/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "frame.h"
#include "render.h"
#include <unistd.h>

static SDL_Renderer *ren = NULL;
static SDL_Texture *tex = NULL;
static SDL_Rect rect;
extern struct simote_now now;

int init_render(SDL_Window *win, int w, int h)
{
	now.render_sem = SDL_CreateSemaphore(1);
	SDL_SemWait(now.render_sem);

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, w, h);

	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;
	return 0;
}

int render_loop(void *wtf)
{
	while(true){
		SDL_SemWait(now.render_sem);
		render_a_frame();
	}
}

int render_a_frame(void)
{
	AVFrame *frame = NULL;
	SDL_LockMutex(now.mutex);
	frame = now.frame_render;
	now.Is_Rendered = false;
	SDL_UnlockMutex(now.mutex);
    if(rect.w != now.width || rect.h != now.height){
		printf("%d %d\n%d %d\n", rect.w, rect.h, now.width, now.height);
		SDL_DestroyTexture(tex);
		rect.w = now.width;
		rect.h = now.height;
		tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
	}

	usleep(500*1000);
	SDL_UpdateYUVTexture(tex, NULL,
	                     frame->data[0], frame->linesize[0],
			     frame->data[1], frame->linesize[1],
			     frame->data[2], frame->linesize[2]);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_LockMutex(now.mutex);
	now.Is_Rendered = true;
	SDL_UnlockMutex(now.mutex);
	return 0;
}
