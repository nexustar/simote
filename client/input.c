#include <SDL2/SDL.h>
#include "network.h"
#include "frame.h"

extern int winw, winh;
extern struct simote_now now;

int input_handle_keydown(SDL_Keycode key)
{
	uint8_t data[10] = "sekd";
	data[4] = key >> 24;
	data[5] = key >> 16;
	data[6] = key >> 8;
	data[7] = key;
	data[8] = 0;
	network_sendudp(data, 8);
	return 0;
}

int input_handle_keyup(SDL_Keycode key)
{
	uint8_t data[10] = "seku";
	data[4] = key >> 24;
	data[5] = key >> 16;
	data[6] = key >> 8;
	data[7] = key;
	data[8] = 0;
	network_sendudp(data, 8);
	return 0;
}

int input_handle_btndown(SDL_Keycode key)
{
	uint8_t data[10] = "semd";
	data[4] = key >> 24;
	data[5] = key >> 16;
	data[6] = key >> 8;
	data[7] = key;
	data[8] = 0;
	network_sendudp(data, 8);
	return 0;
}

int input_handle_btnup(SDL_Keycode key)
{
	uint8_t data[10] = "semu";
	data[4] = key >> 24;
	data[5] = key >> 16;
	data[6] = key >> 8;
	data[7] = key;
	data[8] = 0;
	network_sendudp(data, 8);
	return 0;
}

int input_handle_mouse_moveto(unsigned int x, unsigned int y)
{
	unsigned int sx = x * 4 * now.width / winw;
	unsigned int sy = y * 4 * now.height / winh;
	uint8_t data[10] = "sema";
	data[4] = sx >> 8;
	data[5] = sx;
	data[6] = sy >> 8;
	data[7] = sy;
	data[8] = 0;
	network_sendudp(data, 8);
	return 0;
}
