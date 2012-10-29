/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "../../lib/emokit/band_waves.h"
#include "../../lib/emokit/emokit.h"
#include "../../lib/emokit/emo_dsp.h"
#include "../../lib/emokit/data_headset.h"


void adjustHeadset(emokit_device* d){
	int i;
	int nbUnsetCaptor=0;
	int quit =0;
	char answer;
	
	do{
		for(i=0; i<256; i++){
			if(emokit_read_data(d) > 0)
			{
				emokit_get_next_frame(d);
			}
		}
		for(i=0; i<NB_CHANNELS;i++){
			if(d->contact_quality[i]<3){
				printf("Captor %d is not set up correctly\n", i+1);
				nbUnsetCaptor++;
			}
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

int main(int argc, char **argv)
{
	FILE *input;
	FILE *output;
  
	//Initialize the structure for decoding device data
	emokit_device* d;
	d = emokit_create();
	
	//Create the wave structure which allow us to store filter values
	//for ALPHA WAVES	
	waves* wa;
	wa = new_waves();

	waves* wb;
	wb = new_waves();
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}
	
	adjustHeadset(d);
	
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			emokit_get_next_frame(d);
			//printf("X : %d Y: %d   ", d->current_frame.gyroX, d->current_frame.gyroY);
			int i;
			for(i=0; i<14; i++){
				printf("%u ", d->contact_quality[i]);
			}
			printf("\n");/*
			compute_band_waves(wa,&d->current_frame, ALPHA);
			compute_band_waves(wb,&d->current_frame, BETA);
			
			double averageA,averageB = 0;
			int i;
			
			for(i=0; i<NB_CHANNELS; i++){
				averageA += wa->averaged_epoch[i];
				averageB += wb->averaged_epoch[i];
			}
			averageA = averageA/((double)NB_CHANNELS);
			averageB = averageB/((double)NB_CHANNELS);
			printf("%f\n", averageA/averageB);
			*/
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	deleteWaves(wb);
	deleteWaves(wa);
	return 0;
}
