#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <fcntl.h>    /* File control definitions */
#include <termios.h>  /* POSIX terminal control definitions */


int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, unsigned char* str);
int serialport_read_until(int fd, char* buf, char until);
