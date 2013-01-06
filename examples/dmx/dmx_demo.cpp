/* 
 * demo code for the usbdmx driver
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../../include/dmx512/ofxDmx.h"
/* where do we find the interface */
#define DEVICE "/dev/ttyUSB0"

int main(int argc, char **argv)
{
	ofxDmx* dmx = new ofxDmx();
	int total = 24;
	bool connected = dmx->connect(DEVICE, total);
	if(connected == 1){
		std::cout << "Connection successful\n";
	}else{
		std::cout << "Connection failed\n";
		return 1;
	}
	//int k=0;
	//int i =0;
	//while(true){
		//for(int i=1; i<=total; i++){
			//dmx->setLevel(i, k%255);

	//}
	//dmx->update();
	//int fd = serialport_init(DEVICE, B115200);
	//serialport_writebyte( fd, 0x7E);
	//serialport_writebyte( fd, 6);
	//serialport_writebyte( fd, (total+1) & 0xff);
	//serialport_writebyte( fd, ((total+1) >> 8) & 0xff);
	//serialport_writebyte( fd, 0xE7);
	//int i=0;
	//for(i=0; i<total; i++){
		//serialport_writebyte( fd, 100);
	//}
	//serialport_writebyte( fd, 0x7E);
	return 0;
}
