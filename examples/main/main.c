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

#include "../../lib/emokit/band_waves.h"
#include "../../lib/emokit/emokit.h"
#include "../../lib/emokit/emo_dsp.h"

#define NB_CHANNELS 14

   

int main(int argc, char **argv)
{
	FILE *input;
	FILE *output;
  
	emokit_device* d;
  
	d = emokit_create();

	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}

	struct waves* w;
	w = make_new_waves();
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{

			emokit_get_next_frame(d);
			
			compute_band_waves(w,&d->current_frame);
			double average;
			int i;
			for(i=0; i<NB_CHANNELS; i++){
				average += w->epoch_values[i][0];
			}
			average = average/((double)NB_CHANNELS);
			printf("%f\n", average);
			
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
