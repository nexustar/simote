#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "frame.h"
#include "decode.h"
#include "rtp.h"

static AVCodec *codec = NULL;
static AVCodecContext *cctx = NULL;
extern struct simote_now now;

int init_decode(void)
{
	now.decode_sem = SDL_CreateSemaphore(1);
	SDL_SemWait(now.decode_sem);

	codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	cctx = avcodec_alloc_context3(codec);

	avcodec_open2(cctx, codec, NULL);
	now.frame_decode = av_frame_alloc();
	now.frame_render = av_frame_alloc();
	now.Is_Rendered = true;
	now.Is_Previous_Rendered = false;

	return 0;
}

int decode_loop(void *wtf)
{
	AVPacket packet;
	int isframe;
	
	while(true){
		SDL_SemWait(now.decode_sem);
		isframe = receive_a_packet(&packet);
		avcodec_send_packet(cctx, &packet);
		avcodec_receive_frame(cctx, now.frame_decode);
		now.width = cctx->width;
		now.height = cctx->height;

		frame_swap(&now.frame_decode, &now.frame_render);
		now.Is_Previous_Rendered = now.Is_Rendered;
		now.Is_Rendered = false;
		if(now.Is_Previous_Rendered)
			SDL_SemPost(now.render_sem);
		else
			printf("skip a frame\n");
		//av_packet_unref(&packet);
		free(packet.data);
		free(packet.buf);
		free(packet.side_data);
	}
	return 0;
}

