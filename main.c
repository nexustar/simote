#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>

int main(int argc, char* argv[])
{
	SDL_Window *win = NULL;
	SDL_Renderer *ren = NULL;
	SDL_Texture *tex = NULL;
	SDL_Rect rect;

	AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	AVCodecContext *cctx = avcodec_alloc_context3(codec);
	AVFormatContext *fctx = NULL; //avformat_alloc_context();
	AVPacket packet;
	AVFrame *frame = av_frame_alloc();
	int t;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("simote", 100, 100, atoi(argv[1]), atoi(argv[2]), SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, atoi(argv[1]), atoi(argv[2]));

	avformat_open_input(&fctx, "/dev/stdin", NULL, NULL);
	avcodec_open2(cctx, codec, NULL);

	while((t = av_read_frame(fctx, &packet)) >= 0){
		avcodec_send_packet(cctx, &packet);
		avcodec_receive_frame(cctx, frame);
		SDL_UpdateYUVTexture(tex, NULL,
				frame->data[0], frame->linesize[0],
				frame->data[1], frame->linesize[1],
				frame->data[2], frame->linesize[2]);
		rect.x = 0;
		rect.y = 0;
		rect.w = cctx->width;
		rect.h = cctx->height;
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, &rect);
		SDL_RenderPresent(ren);
		av_packet_unref(&packet);
	}
	SDL_Quit();
	return 0;
}
