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
#include "emokit/emotions.h"
#include "emokit/emokit_dsp.h"


int main(int argc, char **argv)
{
	//****** READ FILE ******
	data* dat;
	//int nbSamples = atoi(argv[2]);
	dat = new_data(argv[1], 1);
	
	//****** DSP struct *****
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();
	
	//***** EMOTIONS *****
	emotions* e;
	e = init_emotions(dsp);
	
	//********* PLOT *****
	plot* p;
	p = init_plot(dsp, e);


	
	if(open_data_file(dat)>0){
			//printf("Error opening the file\nClosing the program\n");
			return 1;
	}
	
	int k=0;
	//printf("Starting read\n");
	while(!feof(dat->fichier))
	{
			struct emokit_frame c;
			c = data_get_next_frame(dat);
			compute_frame(dsp, c);
			
			if(k%INTERVAL==0){
				compute_arousal(e);
				compute_valence(e);
				printf("%e;%e\n", e->arousal, e->valence);
				//printf("%e    %e   %e\n", e->valence_4s, e->valence_20s, e->valence);
				
				//plot_reset(p);
				//plot_average_fourier(p);
				//plot_arousal(p);
				//plot_valence(p);
				//usleep(500000);
			}
			k++;
			fflush(stdout);
	}
	plot_close(p);
	close_data(dat);
	return 0;
}

