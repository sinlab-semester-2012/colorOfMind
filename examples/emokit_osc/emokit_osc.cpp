/*
Simple example of sending an OSC message using oscpack.
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include "../../lib/oscpack/osc/OscOutboundPacketStream.h"
#include "../../lib/oscpack/ip/UdpSocket.h"
#include "../../lib/emokit/emokit.h"
#include "../../lib/emokit/data_headset.h"

#define ADDRESS "127.0.0.1"
#define PORT 9997

#define OUTPUT_BUFFER_SIZE 4096

void sigproc(int i)
{
	std::cout << "closing emokit and quitting" << std::endl;
	exit(0);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, sigproc);
	#ifndef WIN32
	signal(SIGQUIT, sigproc);
	#endif

   	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
   	char buffer[OUTPUT_BUFFER_SIZE];


	FILE *input;
	FILE *output;
	  
	emokit_device* d;
	d = emokit_create();
	
	//Openfile 
	unsigned int packet_nb=atoi(argv[2]);
	data* dat;
	dat = new_data(argv[1], packet_nb);
	openDataFile(dat);
	
	unsigned int count = 0;
	/*printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}*/
	int timer = 0;
	//while(1){
	while(data_get_next_frame(dat, d) == 0 && count < packet_nb){
		emokit_compute_next_frame(d);
		struct emokit_frame frame = d->current_frame;

		//printf("\r\33[2K");	//go back to beginning of line
		printf("gyroX: %d; gyroY: %d; battery: %d\n", frame.gyroX, frame.gyroY, d->battery*100/128);
		//printf(" contact qualities: ");
		/*for(int i=0 ; i<14 ; i++){
		printf("%d ", d->contact_quality[i]);
		}*/

		fflush(output);

		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		osc::OutboundPacketStream q( buffer, OUTPUT_BUFFER_SIZE );
		p << osc::BeginMessage( "/emokit/channels" )
		<< frame.F3 << frame.FC6 << frame.P7 << frame.T8 << frame.F7 << frame.F8 << frame.T7 << frame.P8 << frame.AF4 << frame.F4 << frame.AF3 << frame.O2 << frame.O1 << frame.FC5 << osc::EndMessage;
		    
		transmitSocket.Send( p.Data(), p.Size() );
		
		q << osc::BeginMessage( "/emokit/gyro" )<< (int)frame.gyroX << (int)frame.gyroY << osc::EndMessage;
		
		transmitSocket.Send( q.Data(), q.Size() );
		count++;
		usleep(100000);
	}

	closeFile(dat->fichier);
	emokit_close(d);
	//emokit_delete(d);
	return 0;

}


