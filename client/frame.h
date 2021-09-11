#include <stdbool.h>
#include <SDL2/SDL.h>
#include <libavformat/avformat.h>

struct simote_now {
	AVFrame *frame_decode;
	AVFrame *frame_render;
	int width;
	int height;
	bool Is_Rendered;
	SDL_sem *decode_sem;
	SDL_sem *render_sem;
	SDL_mutex *mutex;
};

long gct(void);
void frame_swap(AVFrame **frame1, AVFrame **frame2);
