#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

static struct libevdev_uinput *uidev;
static int correction_x, correction_y;

void send_key_down(unsigned int key)
{
	libevdev_uinput_write_event(uidev, EV_KEY, key, 1);
	libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
}

void send_key_up(unsigned int key)
{
	libevdev_uinput_write_event(uidev, EV_KEY, key, 0);
	libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
}

void send_mouse_moveto(unsigned int x, unsigned int y)
{
	libevdev_uinput_write_event(uidev, EV_ABS, ABS_X, x + correction_x);
	libevdev_uinput_write_event(uidev, EV_ABS, ABS_Y, y + correction_y);
	libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
}


void init_uidev(int abs_w, int abs_h, int abs_x, int abs_y)
{
	struct libevdev *dev;
	struct input_absinfo absinfo_x = {
		.value = 0,
		.flat = 0,
		.fuzz = 0,
		.maximum = abs_w,
		.minimum = 0,
		.resolution = 0
	};
	struct input_absinfo absinfo_y = {
		.value = 0,
		.flat = 0,
		.fuzz = 0,
		.maximum = abs_h,
		.minimum = 0,
		.resolution = 0
	};

	correction_x = abs_x;
	correction_y = abs_y;
	dev = libevdev_new();
	libevdev_set_name(dev, "simote virtual input");

	libevdev_enable_event_type(dev, EV_ABS);
	libevdev_enable_event_code(dev, EV_ABS, ABS_X, &absinfo_x);
	libevdev_enable_event_code(dev, EV_ABS, ABS_Y, &absinfo_y);

	libevdev_enable_event_type(dev, EV_REL);
	libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
	libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);

	libevdev_enable_event_type(dev, EV_KEY);
	libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_BACKSPACE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_TAB, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_ENTER, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_ESC, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_SPACE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_APOSTROPHE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_COMMA, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_MINUS, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_DOT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_SLASH, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_0, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_1, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_2, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_3, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_4, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_5, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_6, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_7, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_8, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_9, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_SEMICOLON, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_EQUAL, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTBRACE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_BACKSLASH, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHTBRACE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_GRAVE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_A, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_B, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_C, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_D, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_E, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_G, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_H, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_I, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_J, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_K, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_L, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_M, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_N, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_O, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_P, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_Q, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_R, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_S, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_T, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_U, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_V, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_W, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_X, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_Y, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_Z, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_DELETE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_CAPSLOCK, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F1, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F2, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F3, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F4, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F5, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F6, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F7, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F8, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F9, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F10, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F11, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_F12, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_PRINT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_SCROLLLOCK, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_PAUSE, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_INSERT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_HOME, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_PAGEUP, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_END, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_PAGEDOWN, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_DOWN, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_UP, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_NUMLOCK, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTCTRL, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTSHIFT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTALT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTMETA, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHTCTRL, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHTSHIFT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHTALT, NULL);
	libevdev_enable_event_code(dev, EV_KEY, KEY_RIGHTMETA, NULL);

	libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);

}

unsigned int to_linux_KEY(uint32_t sdlkey)
{
	switch(sdlkey){
	case SDL_BUTTON_LEFT:
		return BTN_LEFT;
	case SDL_BUTTON_MIDDLE:
		return BTN_MIDDLE;
	case SDL_BUTTON_RIGHT:
		return BTN_RIGHT;
	case SDLK_BACKSPACE:
		return KEY_BACKSPACE;
	case SDLK_TAB:
		return KEY_TAB;
	case SDLK_RETURN:
		return KEY_ENTER;
	case SDLK_ESCAPE:
		return KEY_ESC;
	case SDLK_SPACE:
		return KEY_SPACE;
	case SDLK_QUOTE:
		return KEY_APOSTROPHE;
	case SDLK_COMMA:
		return KEY_COMMA;
	case SDLK_MINUS:
		return KEY_MINUS;
	case SDLK_PERIOD:
		return KEY_DOT;
	case SDLK_SLASH:
		return KEY_SLASH;
	case SDLK_0:
		return KEY_0;
	case SDLK_1:
		return KEY_1;
	case SDLK_2:
		return KEY_2;
	case SDLK_3:
		return KEY_3;
	case SDLK_4:
		return KEY_4;
	case SDLK_5:
		return KEY_5;
	case SDLK_6:
		return KEY_6;
	case SDLK_7:
		return KEY_7;
	case SDLK_8:
		return KEY_8;
	case SDLK_9:
		return KEY_9;
	case SDLK_SEMICOLON:
		return KEY_SEMICOLON;
	case SDLK_EQUALS:
		return KEY_EQUAL;
	case SDLK_LEFTPAREN:
		return KEY_LEFTBRACE;
	case SDLK_BACKSLASH:
		return KEY_BACKSLASH;
	case SDLK_RIGHTBRACKET:
		return KEY_RIGHTBRACE;
	case SDLK_BACKQUOTE:
		return KEY_GRAVE;
	case SDLK_a:
		return KEY_A;
	case SDLK_b:
		return KEY_B;
	case SDLK_c:
		return KEY_C;
	case SDLK_d:
		return KEY_D;
	case SDLK_e:
		return KEY_E;
	case SDLK_f:
		return KEY_F;
	case SDLK_g:
		return KEY_G;
	case SDLK_h:
		return KEY_H;
	case SDLK_i:
		return KEY_I;
	case SDLK_j:
		return KEY_J;
	case SDLK_k:
		return KEY_K;
	case SDLK_l:
		return KEY_L;
	case SDLK_m:
		return KEY_M;
	case SDLK_n:
		return KEY_N;
	case SDLK_o:
		return KEY_O;
	case SDLK_p:
		return KEY_P;
	case SDLK_q:
		return KEY_Q;
	case SDLK_r:
		return KEY_R;
	case SDLK_s:
		return KEY_S;
	case SDLK_t:
		return KEY_T;
	case SDLK_u:
		return KEY_U;
	case SDLK_v:
		return KEY_V;
	case SDLK_w:
		return KEY_W;
	case SDLK_x:
		return KEY_X;
	case SDLK_y:
		return KEY_Y;
	case SDLK_z:
		return KEY_Z;
	case SDLK_DELETE:
		return KEY_DELETE;
	case SDLK_CAPSLOCK:
		return KEY_CAPSLOCK;
	case SDLK_F1:
		return KEY_F1;
	case SDLK_F2:
		return KEY_F2;
	case SDLK_F3:
		return KEY_F3;
	case SDLK_F4:
		return KEY_F4;
	case SDLK_F5:
		return KEY_F5;
	case SDLK_F6:
		return KEY_F6;
	case SDLK_F7:
		return KEY_F7;
	case SDLK_F8:
		return KEY_F8;
	case SDLK_F9:
		return KEY_F9;
	case SDLK_F10:
		return KEY_F10;
	case SDLK_F11:
		return KEY_F11;
	case SDLK_F12:
		return KEY_F12;
	case SDLK_PRINTSCREEN:
		return KEY_PRINT;
	case SDLK_SCROLLLOCK:
		return KEY_SCROLLLOCK;
	case SDLK_PAUSE:
		return KEY_PAUSE;
	case SDLK_INSERT:
		return KEY_INSERT;
	case SDLK_HOME:
		return KEY_HOME;
	case SDLK_PAGEUP:
		return KEY_PAGEUP;
	case SDLK_END:
		return KEY_END;
	case SDLK_PAGEDOWN:
		return KEY_PAGEDOWN;
	case SDLK_RIGHT:
		return KEY_RIGHT;
	case SDLK_LEFT:
		return KEY_LEFT;
	case SDLK_DOWN:
		return KEY_DOWN;
	case SDLK_UP:
		return KEY_UP;
	case SDLK_NUMLOCKCLEAR:
		return KEY_NUMLOCK;
	case SDLK_LCTRL:
		return KEY_LEFTCTRL;
	case SDLK_LSHIFT:
		return KEY_LEFTSHIFT;
	case SDLK_LALT:
		return KEY_LEFTALT;
	case SDLK_LGUI:
		return KEY_LEFTMETA;
	case SDLK_RCTRL:
		return KEY_RIGHTCTRL;
	case SDLK_RSHIFT:
		return KEY_RIGHTSHIFT;
	case SDLK_RALT:
		return KEY_RIGHTALT;
	case SDLK_RGUI:
		return KEY_RIGHTMETA;
	}
	return 0;
}

