int init_network(char *server_ip, int server_port, int local_port);

int network_getudp(uint8_t *datagram);

int network_sendudp(uint8_t *datagram, int length);

void exit_network(void);

