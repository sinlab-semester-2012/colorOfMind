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

void shiftTable(double t[5][1000]){
	int i,j=0;
	for(j=0; j<5; j++){
		for(i=998; i>=0; i--){
			t[j][i+1] = t[j][i];
		}
	}
}

int main(int argc, char **argv)
{
	struct emokit_device* d;
	d = emokit_create();
	
	//*** DSP struct ***
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();
	
	//********* GNUPLOT *****
	gnuplot_ctrl * h ;
    h = gnuplot_init();
    gnuplot_setstyle(h,"lines");
    gnuplot_set_xlabel(h, "Magnitude") ;
    gnuplot_set_xlabel(h, "F") ;
    double ratio[5][1000];
	
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
	
	int k=0;
	
	//** MAIN LOOP **
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			compute_frame(dsp, c);
			shiftTable(ratio);
			
			ratio[0][0] = dsp->alpha_power[0][0]/dsp->beta_power[0][0]*5/8;
			ratio[1][0] = dsp->alpha_power[1][0]/dsp->beta_power[1][0]*5/8;
			ratio[2][0] = dsp->alpha_power[2][0]/dsp->beta_power[2][0]*5/8;
			ratio[3][0] = dsp->alpha_power[3][0]/dsp->beta_power[3][0]*5/8;
			ratio[4][0] = dsp->alpha_power[4][0]/dsp->beta_power[4][0]*5/8;
			if(k%100==0){
				gnuplot_plot_x(h, ratio[0], 1000, "F3") ;
				gnuplot_plot_x(h, ratio[1], 1000, "F4") ;
				gnuplot_plot_x(h, ratio[2], 1000, "AF3") ;
				gnuplot_plot_x(h, ratio[3], 1000, "AF4") ;
				gnuplot_plot_x(h, ratio[4], 1000, "O2") ;
				//gnuplot_plot_x(h, dsp->average_fourier[0], 32, "sensor F3") ;
				//gnuplot_plot_x(h, dsp->average_fourier[1], 32, "sensor F4") ;
				//gnuplot_plot_x(h, dsp->average_fourier[2], 32, "sensor AF3") ;
				//gnuplot_plot_x(h, dsp->average_fourier[3], 32, "sensor AF4") ;
				//gnuplot_plot_x(h, dsp->average_fourier[4], 32, "sensor O2") ;
				//gnuplot_plot_x(h, ratio[1], 1000, "ratio a/b");
				
				usleep(1000000);	
				gnuplot_resetplot(h);
				//sleep();
			}
			fflush(stdout);
			k++;
		}
	}

	gnuplot_close(h) ;
	emokit_close(d);
	emokit_delete(d);
	return 0;
}
