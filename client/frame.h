#include <stdbool.h>

struct simote_now {
	AVFrame *frame_decode;
	AVFrame *frame_render;
	int width;
	int height;
	bool Is_Rendered;
	bool Is_Previous_Rendered;
};

long gct(void);
void frame_swap(AVFrame **frame1, AVFrame **frame2);
