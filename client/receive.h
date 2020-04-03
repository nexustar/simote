#define IS_A_FRAME_PACKET 1
#define IS_NOT_FRAME_PACKET 2

int init_receive(int port);
int receive_a_packet(int fd, AVPacket *packet);
void exit_receive(int fd);
