#include "emokit/emokit_dsp.h"	
#include <math.h>

emokit_dsp* emokit_dsp_create()
{
	emokit_dsp* dsp = (emokit_dsp*)malloc(sizeof(emokit_dsp));
	memset(dsp,0,sizeof(emokit_dsp));
	
	int i;
	for(i = 0; i< W_SIZE;i++)
    {
        dsp->window[i] = 1.0;
    }
	
	return dsp;
}

int emokit_dsp_free(emokit_dsp* dsp){
	free(dsp);
}

void fft(emokit_dsp* dsp, int channel){
	fftw_plan p;
	//TODO: apply window
	
	p = fftw_plan_dft_1d(W_SIZE, dsp->channels[channel], dsp->f_channels[channel], FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);

}

void free_fft(emokit_dsp* dsp){
	int i;
	for(i=0; i<4; i++){
		free(dsp->channels[i]); 
		free(dsp->f_channels[i]);
	}
}

void hamming_window(double* w){
	int i = 0;
    for(i=0;i<W_SIZE;i++)
        *(w+i) = 0.54 + 0.46*cos(2*M_PI*((double)i/(W_SIZE+1)));
}

void flat_top_window(double* w){
	int j = 0;
    for(j=0;j<W_SIZE;j++)
		*(w+j) = 1-1.93*cos(2*M_PI*((double)j/(W_SIZE+1)))+1.29*cos(4*M_PI*((double)j/(W_SIZE+1)))-0.388*cos(6*M_PI*((double)j/(W_SIZE+1)))+0.032*cos(8*M_PI*((double)j/(W_SIZE+1)));
}

void low_pass(){
	//TODO
}

double compute_power_band_wave(emokit_dsp* dsp, int channel, int f_start, int f_end){
	int j=0;
	//Each interval is 1Hz, n=128 : 
	//frequency = k/T, where T is your total sampling period (T=1/128*W_SIZE = 1sec)
	// => f=k
	//The frequency k/n is the same as the frequency (n-k)/n
	//0=0 64=64, 65=63,
	//Only one entry for k=0 and k=n/2
	//0-64 <=> 0-W_SIZE/2
	long double power = 0;
	int start = floor(f_start*(W_SIZE/2)/64);
	int end = ceil(f_end*(W_SIZE/2)/64);
	for(j=start; j<=end; j++){
		power += (dsp->f_channels[channel][j][0]*dsp->f_channels[channel][j][0]+dsp->f_channels[channel][j][1]*dsp->f_channels[channel][j][1]);
		power += (dsp->f_channels[channel][W_SIZE-j][0]*dsp->f_channels[channel][W_SIZE-j][0]+dsp->f_channels[channel][W_SIZE-j][1]*dsp->f_channels[channel][W_SIZE-j][1]);
    }
    return (double)power;
}

void compute_frame(emokit_dsp* s, struct emokit_frame frame){
	int c;
	for(c=0;c<4;c++)
    {
        //Shift all the frames back
        int i;
        for(i=1;i<W_SIZE;i++)
        {
            (s->channels[c])[i-1][0] = (s->channels[c])[i][0];
            (s->channels[c])[i-1][1] = (s->channels[c])[i][1];
            //(s->filtered_channels[c])[i-1][0] = (s->channels[c])[i][0];
        }
        
        //we update the 4 sensor of interest each after another
        // value is set between -1 and 1
        switch(c){
			case 0:
				(s->channels[c])[W_SIZE-1][0] = ((double)((frame.F3)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case 1:
				(s->channels[c])[W_SIZE-1][0] = ((double)((frame.F4)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case 2:
				(s->channels[c])[W_SIZE-1][0] = ((double)((frame.AF3)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case 3:
				(s->channels[c])[W_SIZE-1][0] = ((double)((frame.AF4)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
		}
        //hamming window
        //processing the fft of the channel
        fft(s,c);
        int j;
        for(j=0; j<W_SIZE; j++){
			s->band_power[c][j] = log((s->f_channels[c])[j][0]*(s->f_channels[c])[j][0]+(s->f_channels[c])[j][1]*(s->f_channels[c])[j][1]);
		}
    }

    //compute_alpha_power(s);
    //compute_beta_power(s);
}
