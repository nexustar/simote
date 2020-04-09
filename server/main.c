#include <stdio.h>
#include <stdint.h>
#include "input.h"
#include "network.h"

int main(int argc, char* argv[])
{
	uint8_t data[1600];
	init_uidev();
	init_network(8848);

	while(network_getudp(data) > 0){
		if(data[0] == 's' && data[1] == 'e'){
			if(data[2] == 'k' && data[3] == 'd')
				send_key_down(to_linux_KEY(network_uint8to32(data+4)));
			if(data[2] == 'k' && data[3] == 'u')
				send_key_up(to_linux_KEY(network_uint8to32(data+4)));
						}
	}
	return 0;
}
