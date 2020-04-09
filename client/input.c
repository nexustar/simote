#include <SDL2/SDL.h>
#include "network.h"

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
