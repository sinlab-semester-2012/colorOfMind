/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>

#include "emokit/emokit.h"
#include "emokit/emokit_dsp.h"
#include "emokit/plot.h"
#include "emokit/emotions.h"
  
void adjustHeadset(struct emokit_device* d);
void initialize_data(struct emokit_device* d, emokit_dsp* dsp);

int main(int argc, char **argv)
{
	//#### INITIALIZE #####
	//*** EMOKIT DEVICE ***
	struct emokit_device* d;
	d = emokit_create();
	
	//*** DATA PROCESSING ***
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();

	//***** EMOTIONS *****
	emotions* e;
	e = init_emotions(dsp);
	
	//********* PLOT *****
	plot* p;
	p = init_plot(dsp, e);

	// #### MENU #####

	//#### CLOSING ####
	plot_close(p);
	emokit_close(d);
	emokit_delete(d);
	return 0;
}


void main_menu(){
	printf("
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


void emokit_loop(){

	//*** Check epoc connected
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
	
	int k=0;
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			
			if(k%32==0){
				compute_arousal(e);
				compute_valence(e);
				printf("%i,%i\n", c.gyroX, c.gyroY);
				//printf("%e    %e   %e\n", e->arousal_4s, e->arousal_20s, e->arousal);
				//printf("%e    %e   %e\n", e->valence_4s, e->valence_20s, e->valence);
				
				//plot_reset(p);
				//plot_arousal(p);
				//plot_valence(p);
				//usleep(1000000);	

			}
			fflush(stdout);
			k++;
		}
	}
}
void read_loop(){}
void save_data(){}
void study(){}
