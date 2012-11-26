/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <unistd.h> //for usleep()
#include "../../include/oscpack/osc/OscOutboundPacketStream.h"
#include "../../include/oscpack/ip/UdpSocket.h"

extern "C"
{
#include "emokit/emokit.h"
//#include "../../lib/emokit/emo_dsp.h"
//#include "../../lib/emokit/data_headset.h"
}


#define ADDRESS "127.0.0.1"
#define PORT 9000

#define OUTPUT_BUFFER_SIZE 4096
 

//void adjustHeadset(emokit_device* d){
	//int i;
	//int nbUnsetCaptor=0;
	//int quit =0;
	//char answer;
	
	//do{
		//for(i=0; i<256; i++){
			//if(emokit_read_data(d) > 0)
			//{
				//emokit_get_next_frame(d);
			//}
		//}
		//if(d->contact_quality[0]<3){
				//printf("Captor F3 is not set up correctly\n");
				//nbUnsetCaptor++;
		//}
		//if(d->contact_quality[8]<3){
				//printf("Captor AF4 is not set up correctly\n");
				//nbUnsetCaptor++;
		//}
		//if(d->contact_quality[9]<3){
				//printf("Captor F4 is not set up correctly\n");
				//nbUnsetCaptor++;
		//}
		//if(d->contact_quality[10]<3){
				//printf("Captor F3 is not set up correctly\n");
				//nbUnsetCaptor++;
		//}
		//if(nbUnsetCaptor == 0){
			//printf("All captors are set up correctly. Launching the program\n");
			//quit = 1;
		//}
		//else{
			//printf("Please Adjust headset. Continue anyway ? y/n\n");
			//scanf("%c", &answer);
			//if(answer == 'y' || answer == 'Y'){
				//quit =1;
			//}
		//}
	//}while(!quit);
//}

int main(int argc, char **argv)
{
 
	emokit_device* d;
	d = emokit_create();
	//####### TEST CONNECTION ########
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}
	//adjustHeadset(d);
	//########## LOADING FILE ########
	//unsigned int packet_nb = atoi(argv[2]);
	//data* dat;
	//dat = new_data(argv[1], packet_nb);
	//openDataFile(dat);
	//int counter = 0;

	//############## OSC #############
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
	char buffer[OUTPUT_BUFFER_SIZE];
	char raw_frame[32];
	struct emokit_frame frame;
	
	//############## FFT #############
	//emo_dsp_state* s;
	//s = make_new_dsp_state();

	printf("sending data\n");
	//*******************************************************************
	while(1)
	//while(data_get_next_frame(dat, d) == 0 && counter < packet_nb)
	{
		if(emokit_read_data(d) > 0)
		{
			emokit_get_next_frame(d);
			//emokit_compute_next_frame(d);
			//struct emokit_frame frame = d->current_frame;
			
			//#################################
			//######## UNENC RAW DATA #########
			//#################################
			//osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
			//p << osc::BeginMessage( "/emokit/channels" )
			  //<< frame.F3 << frame.FC6 << frame.P7 << frame.T8 << frame.F7 << frame.F8 
			  //<< frame.T7 << frame.P8 << frame.AF4 << frame.F4 << frame.AF3 << frame.O2 
			  //<< frame.O1 << frame.FC5 
			  //<< osc::EndMessage;
			//transmitSocket.Send( p.Data(), p.Size() );
			
			//osc::OutboundPacketStream q( buffer, OUTPUT_BUFFER_SIZE );
			//q << osc::BeginMessage( "/emokit/gyro" ) 
			  //<< (int)frame.gyroX << (int)frame.gyroY << osc::EndMessage;
			//transmitSocket.Send( q.Data(), q.Size() );


			//#################################
			//############ RATIO ##############
			//#################################
			//process_frame(s, &d->current_frame);		
			//osc::OutboundPacketStream r( buffer, OUTPUT_BUFFER_SIZE );
			//r << osc::BeginMessage( "/emokit/ratio" ) 
			  //<< (float)(s->average_beta_power[8]/s->average_alpha_power[8]/2+s->average_beta_power[10]/s->average_alpha_power[10]/2) 
			  //<< (float)(s->average_beta_power[8]/s->average_alpha_power[8]-s->average_beta_power[10]/ s->average_alpha_power[10])
			  //<< osc::EndMessage;
			//transmitSocket.Send( r.Data(), r.Size() );
			//printf("%f \n",s->average_beta_power[8]/s->average_alpha_power[8]/2+s->average_beta_power[10]/s->average_alpha_power[10]/2);
			//printf("%f\n",s->average_beta_power[0]/ s->average_alpha_power[0]);
			//printf("%f\n",s->f_channels[0][0][0]);

		
		//counter++;
		//usleep(5000);
		}
	}

	fflush(stdout);
	//closeFile(dat->fichier);
	emokit_close(d);
	emokit_delete(d);
	return 0;
}
