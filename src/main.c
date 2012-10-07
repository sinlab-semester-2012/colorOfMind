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
#include <gtk/gtk.h>

#include "../lib/emokit.h"
#include "../lib/emo_dsp.h"

   

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
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{

			emokit_get_next_frame(d);
			
			int i = 0;
			while(i<14){
				//printf("%d:%d-",i, d->contact_quality[i]);	
				i++;		
			}
			//printf("\n");
			//FFTW lib with emo_dsp.c			
			//emo_dsp_state* eds;
			//eds = make_new_dsp_state();
			//fft_channel(eds,1);
			//printf("channel Power Number: %f\n", eds->c_power[1]);
	
			//printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
			//printf("%d %d %d %d %d\n", d->current_frame.gyroX, d->current_frame.gyroY, d->current_frame.F3, d->current_frame.FC6, d->current_frame.P7);
		  
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
