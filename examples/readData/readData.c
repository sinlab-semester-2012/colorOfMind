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
#include "emokit/emokit_dsp.h"
#include "gnuplot/gnuplot_i.h"

void shiftTable(double* t){
	int i=0;
	for(i=998; i>=0; i--){
		t[i+1]=t[i];
	}
}

int main(int argc, char **argv)
{
	//****** READ FILE ******
	data* dat;
	int nbSamples = atoi(argv[2]);
	dat = new_data(argv[1], nbSamples);
	
	//****** DSP struct *****
	emokit_dsp* dsp;
	dsp = emokit_dsp_create();
	
	
	//********* GNUPLOT *****
	gnuplot_ctrl * h ;
    h = gnuplot_init();
    gnuplot_setstyle(h,"lines");
    double ratio[1000];

    //gnuplot_plot_equation(h, "sin(x)", "sine on first session");
    //sleep(3);

	
	if(open_data_file(dat)>0){
			printf("Error opening the file\nClosing the program\n");
			return 1;
	}
	
	int i=0;
	for(i=0; i<1000; i++){
		struct emokit_frame c;
		c = data_get_next_frame(dat);
		compute_frame(dsp, c);
		shiftTable(ratio);
		ratio[0]= compute_power_band_wave(dsp,0,8,12)/compute_power_band_wave(dsp,0,16,24);
	}
	int k=0;
	printf("Starting read\n");
	while(1)
	{
			struct emokit_frame c;
			c = data_get_next_frame(dat);
			if(c.F3 == 0){
				break;
			}
			compute_frame(dsp, c);
			
			//printf("%d %d %d %d %d\n", (int)c.gyroX, (int)c.gyroY, c.F3, c.FC6, c.P7);
			//printf("%e, %e %e %e\n", dsp->channels[0][0][0], dsp->channels[1][0][0],dsp->channels[2][0][0], dsp->channels[3][0][0]);
			//printf("%e, %e\n", compute_power_band_wave(dsp,0,8,12),compute_power_band_wave(dsp,1,8,12));
			if(k%1==0){
				shiftTable(ratio);
				usleep(100);
				ratio[0]= compute_power_band_wave(dsp,0,8,12)/compute_power_band_wave(dsp,0,16,24);
				gnuplot_resetplot(h);	
				//gnuplot_plot_x(h, dsp->band_power[0], 1000, "parabola") ;
				gnuplot_plot_x(h, ratio, 1000, "ratio") ;
				//sleep();
			}
			k++;
			fflush(stdout);
	}
	gnuplot_close(h);
	close_data(dat);
	return 0;
}

