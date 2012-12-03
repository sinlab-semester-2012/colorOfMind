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
#include "emokit/read_data.h"
#include "emokit/plot.h"
//#include "emokit/emokit_dsp.h"


int main(int argc, char **argv)
{
	//****** READ FILE ******
	data* dat;
	int nbSamples = atoi(argv[2]);
	dat = new_data(argv[1], nbSamples);
	
	//****** DSP struct *****
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();
	
	
	//********* PLOT *****
	plot* p;
	p = init_plot(dsp);


	
	if(open_data_file(dat)>0){
			printf("Error opening the file\nClosing the program\n");
			return 1;
	}
	
	int k=0;
	printf("Starting read\n");
	while(!feof(dat->fichier))
	{
			struct emokit_frame c;
			c = data_get_next_frame(dat);
			compute_frame(dsp, c);
			
			if(k%100==0){
				plot_reset(p);
				plot_fourier(p);
				usleep(100000);
			}
			k++;
			fflush(stdout);
	}
	plot_close(p);
	close_data(dat);
	return 0;
}

