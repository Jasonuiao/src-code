#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>

typedef struct {
	int p;
	char *buf;
}Packet;

typedef struct {
	Packet pak;
	int pix;
}Pixel;

static int internrl(int argc, char **argv)
{
	//int ret1 = open("/dev/sda", O_RDONLY, 0600);
	//int ret2 = open("/dev/sda", O_RDONLY, 0);
	return 0;
}

