/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>

#include "emokit/emokit_dsp.h"
#include "emokit/emokit.h"
#include "gnuplot/gnuplot_i.h"
  
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

void shiftTable(double* t){
	int i=0;
	for(i=998; i>=0; i--){
		t[i+1]=t[i];
	}
}

int main(int argc, char **argv)
{
	struct emokit_device* d;
	d = emokit_create();
	
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();
	
	//********* GNUPLOT *****
	gnuplot_ctrl * h ;
    h = gnuplot_init();
    gnuplot_setstyle(h,"lines");
    double ratio[1000];
	
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 1);
	if(r != 0)
	{
		printf("CANNOT CONNECT: %d\n", r);
		return 1;
	}
	printf("Connected\n");
	
	adjustHeadset(d);
	int k=0;
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			//printf("%d %d %d %d %d %d\n", c.counter, c.gyroX, c.gyroY, c.F3, c.FC6, c.P7);
			//printf("%e, %e\n", dsp->channels[0][0][0], dsp->channels[1][0][0]);
			//printf("%e | %e | %e | %e \n", compute_power_band_wave(dsp,0,8,12)/compute_power_band_wave(dsp,0,16,24),compute_power_band_wave(dsp,1,8,12)/compute_power_band_wave(dsp,1,16,24),compute_power_band_wave(dsp,2,8,12)/compute_power_band_wave(dsp,2,16,24),compute_power_band_wave(dsp,3,8,12)/compute_power_band_wave(dsp,3,16,24));
			if(k%10==0){
				shiftTable(ratio);
				//ratio[0]= compute_power_band_wave(dsp,1,8,12)/compute_power_band_wave(dsp,1,16,24);
				ratio[0] = (double)c.F3;
				gnuplot_resetplot(h);	
				//gnuplot_plot_x(h, dsp->band_power[0], 1000, "power") ;
				gnuplot_plot_x(h, ratio, 1000, "ratio") ;
				//sleep();
			}
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
