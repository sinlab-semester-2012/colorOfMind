#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <unistd.h> //for usleep()
#include "../../include/oscpack/osc/OscOutboundPacketStream.h"
#include "../../include/oscpack/ip/UdpSocket.h"

extern "C"{
#include "emokit/emokit.h"
#include "emokit/emokit_dsp.h"
#include "emokit/plot.h"
#include "emokit/emotions.h"
#include "emokit/save_data.h"
}

#define MLIVE 0
#define MREAD 0
#define MSAVE 0
#define MEXPERIMENT 0
#define MOSC 0

#define ADDRESS "127.0.1.1"
#define PORT 9997

#define OUTPUT_BUFFER_SIZE 4096
  
void adjust_headset(struct emokit_device* d);
void initialize_data(struct emokit_device* d, emokit_dsp* dsp);
void main_menu(struct emokit_device* d, emokit_dsp* dsp, emotions* e, data* dat, plot* p, char* buffer);
int plot_menu();
void emokit_connect(struct emokit_device* d);
void emokit_loop(struct emokit_device* d, emokit_dsp* dsp, emotions* e, plot* p, char* buffer, int choice);
void read_loop(data* dat, emokit_dsp* dsp, emotions* e,plot* p, char* buffer, int choice);
void save_data(struct emokit_device* d, data* dat);
void osc_message(struct emokit_frame* frame, emokit_dsp* dsp, char* buffer);
void show(int c, struct emokit_frame frame, emokit_dsp* dsp, emotions* e, plot* p, char* buffer);
void print_data(struct emokit_frame frame);

static UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );  

int main(int argc, char **argv)
{
	//#### INITIALIZE #####
	//*** EMOKIT DEVICE ***
	struct emokit_device* d;
	d = emokit_create();
	
	//*** DATA PROCESSING ***
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();

	//*** EMOTIONS ***
	emotions* e;
	e = init_emotions(dsp);
	
	//****** READ FILE ******
	data* dat;
	
	//*** PLOT ***
	plot* p;
	p = init_plot(dsp, e);
	
	//*** OSC ***
	UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );    
	char buffer[OUTPUT_BUFFER_SIZE];

	// #### MENU #####
	main_menu(d,dsp,e,dat,p,buffer);
	//#### CLOSING ####
	fflush(stdout);
	close_data(dat);
	plot_close(p);
	emokit_close(d);
	emokit_delete(d);
	return 0;
}


void main_menu(struct emokit_device* d, emokit_dsp* dsp, emotions* e,data* dat, plot* p, char* buffer){
	int choice = 0;
	std::cout << "\n======================\n"
	<<"colorOfMind :: DevMode\n\n" 
	<< "1.Use Emotiv Epoc headset\n"
	<< "2.Read Data from file\n"
	<< "3.Save Data to file\n"
	<< "Enter a number and press enter :\n";
	while(choice < 1 || choice > 3){
		sleep(1);
		std::cin >> choice;
	}
	int c;
	switch(choice){
		case 1:
			c = plot_menu();
			emokit_connect(d);
			initialize_data(d, dsp);
			adjust_headset(d);
			emokit_loop(d,dsp,e,p,buffer,c);
			break;
		case 2:
			c = plot_menu();
			read_loop(dat, dsp,e, p,buffer, c);
			break;
		case 3:
			save_data(d,dat);
			break;
		default:
			std::cout << "Error no such choice available\n";
	}
}

//Sub menu to chose which information to show
int plot_menu(){
	int choice = 0;
	std::cout << "Choose what you want to print\n\n" 
	<< "1.print Headset values\n"
	<< "2.Plot of raw EEG data\n"
	<< "3.Plot of Fourier Transform\n"
	<< "4.Plot of Arousal-Valence\n"
	<< "5.Send OSC values\n"
	<< "6. Print Arousal-Valence values\n"
	<< "Enter a number and press enter :\n";
	while(choice <1 || choice > 6){
		std::cin >> choice;
	}
	return choice;
}

void initialize_data(struct emokit_device* d, emokit_dsp* dsp){
	int i=0;
	while(i<W_SIZE)
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

  
void adjust_headset(struct emokit_device* d){
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

void emokit_connect(struct emokit_device* d){
	std::cout <<"Current epoc devices connected: " << emokit_get_count(d, EMOKIT_VID, EMOKIT_PID) << "\n";
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 1);
	if(r != 0)
	{
		std::cout << "CANNOT CONNECT: " << r << "\n";
		return;
	}
	std::cout << "Connected\n";
}
void emokit_loop(struct emokit_device* d, emokit_dsp* dsp, emotions* e, plot* p, char* buffer, int choice){
	int k=0;
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			if(k%64==0){
				compute_arousal(e);
				compute_valence(e);
				show(choice, c, dsp,e, p, buffer);
			}

			k++;
		}
	}
}
void read_loop(data* dat, emokit_dsp* dsp, emotions* e, plot* p, char* buffer, int choice){
	char buff[50];
	std::cout << "Enter the file path :\n";
	do{
		std::cin >> buff;
		dat = new_data(buff, 1);
	}while(open_data_file(dat)>0);
	
	int k=0;
	while(!feof(dat->fichier))
	{
			struct emokit_frame c;
			c = data_get_next_frame(dat);
			compute_frame(dsp, c);
			if(k%64==0){
				compute_arousal(e);
				compute_valence(e);
			}
			show(choice, c, dsp, e, p, buffer);
			k++;
			usleep(10000);
	}	
}

void save_data(struct emokit_device* d, data* dat){
	emokit_connect(d);
	char buff[50];
	int t;
	std::cout << "Enter the recording time: \n";
	do{
		std::cin >> t;
	}while(t<= 0 && t>=100000);
	std::cout << "Enter the file path :\n";
	do{
		std::cin >> buff;
		dat = new_data(buff, t);
	}while(create_data_file(dat)>0);

	//write data in file
	write_data(dat, d);
}
void osc_message(struct emokit_frame frame, emokit_dsp* dsp, emotions* e, char* buffer){
	osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
	p << osc::BeginMessage( "/emokit/channels" )
		<< frame.F3 << frame.FC6 << frame.P7 << frame.T8 << frame.F7 << frame.F8 
		<< frame.T7 << frame.P8 << frame.AF4 << frame.F4 << frame.AF3 << frame.O2 
		<< frame.O1 << frame.FC5 
		<< osc::EndMessage;
	transmitSocket.Send( p.Data(), p.Size());
	
	osc::OutboundPacketStream q( buffer, OUTPUT_BUFFER_SIZE );
	q << osc::BeginMessage( "/emokit/gyro" ) 
		<< (int)frame.gyroX << (int)frame.gyroY << osc::EndMessage;
	transmitSocket.Send( q.Data(), q.Size() );
	
	osc::OutboundPacketStream r( buffer, OUTPUT_BUFFER_SIZE );
	r << osc::BeginMessage( "/emokit/emotions" ) 
		<< (int)e->arousal << (int)e->valence << osc::EndMessage;
	transmitSocket.Send( q.Data(), q.Size() );
}

void show(int c, struct emokit_frame frame, emokit_dsp* dsp, emotions* e, plot* p, char* buffer){
	switch(c){
	case 1:
		print_data(frame);
		break;
	case 2:
		//TODO: add EEG channel print in plot.c
		break;
	case 3:
		plot_reset(p);
		plot_average_fourier(p);
		break;
	case 4:
		plot_reset(p);
		plot_arousal(p);
		plot_valence(p);	
		break;
	case 5:
		osc_message(frame, dsp, e, buffer);
		break;
	case 6:
		std::cout<< e->arousal <<" "<< e->valence<<"\n";
	default:
		return;
	}
}
void print_data(struct emokit_frame frame){
	std::cout << "\r\33[2K" << "gyroX: " << (int)frame.gyroX
	<< "; gyroY: " << (int)frame.gyroY
	<< "; F3: " << frame.F3
	<< "; FC6: " << frame.FC6
	<< "; battery: " << (int)frame.battery << "%";

	flush(std::cout);
}


