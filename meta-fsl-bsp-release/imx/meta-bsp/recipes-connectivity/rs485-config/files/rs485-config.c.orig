#include <linux/serial.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Driver-specific ioctls: */
#define TIOCGRS485      0x542E
#define TIOCSRS485      0x542F

int main(void)
{
	struct serial_rs485 rs485conf;

	printf("enable rs485 mode ...\n");

	// initialize rs485 struct
	memset(&rs485conf, 0, sizeof(rs485conf));

	// open com3
	int fd_com3 = open ("/dev/ttymxc2", O_RDWR);

	if (fd_com3 < 0) {
		printf("com3 cannot be opened (fd = %d)\n", fd_com3);
		exit(1);
	}

	// set RS485 mode
	rs485conf.flags |= SER_RS485_ENABLED;
	if (ioctl (fd_com3, TIOCSRS485, &rs485conf) < 0) {
		printf("rs485 cannot be enabled on com3\n");
		exit(1);
	}

	// close com3
	if (close (fd_com3) < 0) {
		printf("com3 cannot be closed\n");
	}

	// open com4
	int fd_com4 = open ("/dev/ttymxc3", O_RDWR);

	if (fd_com4 < 0) {
		printf("com4 cannot be opened (fd = %d)\n", fd_com4);
		exit(1);
	}

	// set RS485 mode
	if (ioctl (fd_com4, TIOCSRS485, &rs485conf) < 0) {
		printf("rs485 cannot be enabled on com4\n");
		exit(1);
	}

	// close com4
	if (close (fd_com4) < 0) {
		printf("com4 cannot be closed\n");
	}

#if 0
	// open com5
	int fd_com5 = open ("/dev/ttymxc4", O_RDWR);

	if (fd_com5 < 0) {
		printf("com5 cannot be opened (fd = %d)\n", fd_com5);
		exit(1);
	}

	// set RS485 mode
	if (ioctl (fd_com5, TIOCSRS485, &rs485conf) < 0) {
		printf("rs485 cannot be enabled on com5\n");
		exit(1);
	}

	// close com5
	if (close (fd_com5) < 0) {
		printf("com5 cannot be closed\n");
	}
#endif
}
