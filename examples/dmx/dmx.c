//#include <sys/ioctl.h>
//#include <getopt.h>
//#include <unistd.h>   /* UNIX standard function definitions */
//#include <errno.h>    /* Error number definitions */
#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <fcntl.h>    /* File control definitions */
#include <termios.h>  /* POSIX terminal control definitions */

#include "emokit/emokit.h"
#include "emokit/read_data.h"
#include "emokit/emokit_dsp.h"
#include "emokit/emotions.h"


int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);


void adjustHeadset(struct emokit_device* d);
void initialize_data(struct emokit_device* d, emokit_dsp* dsp);

int main(int argc, char **argv) 
{
	struct emokit_device* d;
	d = emokit_create();
	
	//****** READ FILE ******
	//data* dat;
	////int nbSamples = atoi(argv[2]);
	//dat = new_data(argv[1],1);
	
	//*** DSP struct ***
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();

	//***** EMOTIONS *****
	emotions* e;
	e = init_emotions(dsp);
	
    int fd,k = 0;
    unsigned char buff_arousal[2];
    unsigned char buff_valence[2];
    buff_arousal[0] = 100;
    buff_valence[0] = 200;
    char serialport[256] = "/dev/ttyACM0";
    int baudrate = B57600;  // default
    int wr;
    fd = serialport_init("/dev/ttyACM0", baudrate);
    
    
    //**FILE ****
	//if(open_data_file(dat)>0){
			//printf("Error opening the file\nClosing the program\n");
			//return 1;
	//}
	
	
	//** EMOKIT
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 1);
	if(r != 0)
	{
		printf("CANNOT CONNECT: %d\n", r);
		return 1;
	}
	printf("Connected\n");
	
	adjustHeadset(d);
	initialize_data(d,dsp);
    
    
    //*** TEST ARDUINO CONNECTED
    if (fd == -1 )
	{
		exit(EXIT_FAILURE);
	}
		
    //while(dat->play != 0)
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
	
			struct emokit_frame c;
			//c = data_get_next_frame(dat);
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			
			if(k%32==0){
				compute_arousal(e);
				compute_valence(e);

				buff_arousal[1] = (int)((e->arousal+1)*128);
				buff_valence[1] = (int)((e->valence+1)*128);
				printf("%i %i\n", buff_arousal[1], buff_valence[1]);
				printf("%e %e\n", e->arousal+1, e->valence+1);
				if(k%64 == 0){
					wr=serialport_write(fd,buff_arousal);
					//sleep(1);
					wr=serialport_write(fd,buff_valence);
				}

			}
			k++;
			usleep(5000);
		}
	}
	//close_data(dat);
	printf("Finish\n");
	return 0;
  
} 

void initialize_data(struct emokit_device* d, emokit_dsp* dsp){
	int i=0;
	while(i<W_SIZE*2)
	{
		if(emokit_read_data(d) > 0)
		{
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			i++;
		}
	}
}

void adjustHeadset(struct emokit_device* d){
	int i;
	int nbUnsetCaptor=0;
	int quit =0;
	char answer;
	struct emokit_frame c;
	do{
		for(i=0; i<256; i++){
			if(emokit_read_data(d) > 0)
			{
				c = emokit_get_next_frame(d);
			}
		}
		nbUnsetCaptor=0;
		if(c.cq.F3<4000){
			printf("Captor F3 is not set up correctly, value : %i\n", c.cq.F3);
			nbUnsetCaptor++;
		}
		if(c.cq.F4<4000){
			printf("Captor F4 is not set up correctly, value : %i\n", c.cq.F4);
			nbUnsetCaptor++;
		}
		if(c.cq.AF3<4000){
			printf("Captor AF3 is not set up correctly, value : %i\n", c.cq.AF3);
			nbUnsetCaptor++;
		}
		if(c.cq.AF4<4000){
			printf("Captor AF4 is not set up correctly, value : %i\n", c.cq.AF4);
			nbUnsetCaptor++;
		}
		if(c.cq.O2<4000){
			printf("Captor O2 is not set up correctly, value : %i\n", c.cq.O2);
			nbUnsetCaptor++;
		}
		if(nbUnsetCaptor == 0){
			printf("All captors are set up correctly. Launching the program\n");
			quit = 1;
		}
		else{
			printf("Please Adjust headset. Continue anyway ? y/n\n");
			scanf(" %c", &answer);
			if(answer == 'y' || answer == 'Y'){
				quit =1;
			}
		}
	}while(!quit);
}   

// end main
    
int serialport_writebyte( int fd, uint8_t b)
{
    int n = write(fd,&b,1);
    if( n!=1)
        return -1;
    return 0;
}

int serialport_write(int fd, const char* str)
{
    int len = strlen(str);
    int n = write(fd, str, len);
    if( n!=len ) 
        return -1;
    return 0;
}

int serialport_read_until(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;
    } while( b[0] != until );

    buf[i] = 0;  // null terminate the string
    return 0;
}

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int serialport_init(const char* serialport, int baud)
{
    struct termios toptions;
    int fd;
    
    //fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",
    //        serialport,baud);

    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0) {
        perror("init_serialport: Couldn't get term attributes");
        return -1;
    }
    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
    case 4800:   brate=B4800;   break;
    case 9600:   brate=B9600;   break;
#ifdef B14400
    case 14400:  brate=B14400;  break;
#endif
    case 19200:  brate=B19200;  break;
#ifdef B28800
    case 28800:  brate=B28800;  break;
#endif
    case 38400:  brate=B38400;  break;
    case 57600:  brate=B57600;  break;
    case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;

    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;
    
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return -1;
    }

    return fd;
}
