int init_network(int port);

int network_getudp(uint8_t *datagram, char *ip, int *port);

void exit_network(void);

uint32_t network_uint8to32(uint8_t* data);

