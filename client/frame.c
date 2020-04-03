#include <libavformat/avformat.h>
#include "frame.h"

struct simote_now now;
void frame_swap(AVFrame **frame1, AVFrame **frame2)
{
	AVFrame *t;
	t = *frame1;
	*frame1 = *frame2;
	*frame2 = t;
}
