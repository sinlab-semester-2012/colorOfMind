#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../lib/emokit/emokit.h"
#include "../../lib/emokit/data_headset.h"
#include "../../lib/emokit/band_waves.h"

int main(int argc, char **argv)
{
	//Initialize the structure for decoding device data
	emokit_device* d;
	d = emokit_create();
	
	unsigned int packet_nb = atoi(argv[2]);
	
	data* dat;
	dat = new_data(argv[1], packet_nb);
	openDataFile(dat);
	//should return value to know if everything ok
	int count = 0;
	
	//Create the wave structure which allow us to store filter values
	//for ALPHA WAVES	
	
	waves* wa;
	wa = new_waves();
	waves* wb;
	wb = new_waves();
	
	
	while(data_get_next_frame(dat, d) == 0 && count < packet_nb){
		emokit_compute_next_frame(d);
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
		
		//printf("X : %d Y: %d   \n", d->current_frame.gyroX, d->current_frame.gyroY);
		count++;
		usleep(1000);
	}

	
	fflush(stdout);
	closeFile(dat->fichier);
	emokit_close(d);
	emokit_delete(d);
	
	deleteWaves(wb);
	deleteWaves(wa);
	
	return 0;
}


