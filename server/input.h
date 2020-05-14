void send_key_down(unsigned int key);

void send_key_up(unsigned int key);

void send_btn_down(unsigned int key);

void send_btn_up(unsigned int key);

void send_mouse_moveto(unsigned int x, unsigned int y);

void init_absmouse(int abs_w, int abs_h, int abs_x, int abs_y);

void init_relmouse(void);

void init_keyboard(void);

void set_mouse(char mouse);

unsigned int to_linux_KEY(uint32_t sdlkey);

