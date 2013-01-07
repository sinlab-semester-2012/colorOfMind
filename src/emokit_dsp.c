#include "emokit/emokit_dsp.h"	
#include <math.h>

emokit_dsp* emokit_dsp_create()
{
	emokit_dsp* dsp = (emokit_dsp*)malloc(sizeof(emokit_dsp));
	memset(dsp,0,sizeof(emokit_dsp));
	int i,j,k;
	for(i=0; i<NB_CHANNEL; i++){
		for(j=0; j<W_SIZE; j++){
			dsp->channels[i][j][0] = 0;
			dsp->filtered_channels[i][j][0]=0;
			for(k=0; k<HISTORY; k++){
				dsp->band_power[i][j][k]=0;
			}
		}
	}
	
	dsp->counter=0;
	
	//chose window
    //no_window(dsp->window);
	hamming_window(dsp->window);
	
	return dsp;
}

int emokit_dsp_free(emokit_dsp* dsp){
	free(dsp);
}

void fft(emokit_dsp* dsp, int channel){
	fftw_plan p;
	
	//Pointer to the channels data
    //fftw_complex* channelValue = dsp->channels[channel];
    fftw_complex* channelValue = dsp->channels[channel];

    //Window the measurements 
    int i=0;
    for(i=0;i<W_SIZE;i++)
    {
        dsp->windowed[i][0] = dsp->window[i]*channelValue[i][0];
        //dsp->windowed[i][1] = dsp->window[i]*channelValue[i][1];
    }
 
    //FFT the frame
	p = fftw_plan_dft_1d(W_SIZE, dsp->windowed, dsp->f_channels[channel], FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);

}


void free_fft(emokit_dsp* dsp){
	int i;
	for(i=0; i<NB_CHANNEL; i++){
		free(dsp->channels[i]); 
		free(dsp->f_channels[i]);
	}
}

//Hamming_windows : default window
void hamming_window(double* w){
	int i = 0;
    for(i=0;i<W_SIZE;i++)
        *(w+i) = 0.54 - 0.46*cos(2*M_PI*((double)i/(W_SIZE+1)));
}

//Flat top window : not used in this program
void flat_top_window(double* w){
	int j = 0;
    for(j=0;j<W_SIZE;j++)
		*(w+j) = 1-1.93*cos(2*M_PI*((double)j/(W_SIZE+1)))+1.29*cos(4*M_PI*((double)j/(W_SIZE+1)))-0.388*cos(6*M_PI*((double)j/(W_SIZE+1)))+0.032*cos(8*M_PI*((double)j/(W_SIZE+1)));
}

//set the windows to a rectangular window
void no_window(double* w){
	int i=0;
    for(i=0;i<W_SIZE;i++)
    {
        *(w+i) = 1;
    }
}

double compute_power_band_wave(emokit_dsp* dsp, int channel, int f_start, int f_end){
	int j=0;
	//frequency = k/T, where T is your total sampling period (T=1/128*W_SIZE = 1sec)
	//The frequency k/n is the same as the frequency (n-k)/n - Only one entry for k=0 and k=n/2

	long double power = 0;
	int start = floor(f_start*(W_SIZE/2)/64);
	int end = ceil(f_end*(W_SIZE/2)/64);
	for(j=start; j<=end; j++){
		power += (dsp->f_channels[channel][j][0]*dsp->f_channels[channel][j][0]+dsp->f_channels[channel][j][1]*dsp->f_channels[channel][j][1]);
		power += (dsp->f_channels[channel][W_SIZE-j][0]*dsp->f_channels[channel][W_SIZE-j][0]+dsp->f_channels[channel][W_SIZE-j][1]*dsp->f_channels[channel][W_SIZE-j][1]);
    }
    return (double)power;
}

void compute_frame(emokit_dsp* dsp, struct emokit_frame frame){
	int c;
	//classify_frame(dsp->cf, frame);
	for(c=0;c<NB_CHANNEL;c++)
    {
        //Shift all the frames back
        int i;
        mean(dsp, c);
        for(i=1;i<W_SIZE;i++)
        {
            (dsp->channels[c])[i-1][0] = (dsp->channels[c])[i][0];
            (dsp->filtered_channels[c])[i-1][0] = (dsp->channels[c])[i][0];
            dsp->value[c][i-1] = dsp->value[c][i];
        }
        
        //we update the NB_CHANNEL sensor - value is set between -1 and 1
        switch(c){
			case F3_SENSOR:
				dsp->value[c][W_SIZE-1] = frame.F3;
				mean(dsp,c);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F3)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE; //sin(dsp->counter/5);
				break;
			case F4_SENSOR:
				dsp->value[c][W_SIZE-1] = frame.F4;
				mean(dsp,c);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F4)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE;
				break;
			case F3AF3:
				dsp->value[c][W_SIZE-1] = frame.F3-frame.AF3;
				mean(dsp,c);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F3-frame.AF3)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE;
				//(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F3)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE;
				break;
			case F4AF4:
				dsp->value[c][W_SIZE-1] = frame.F4-frame.AF4;
				mean(dsp,c);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F4-frame.AF4)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE;
				//(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F4)-dsp->mean[c]))/(double)MAX_SENSOR_VALUE;
				break;
			default:
				printf("Error in compute_frame(). Shouldn't be here");
				break;
		}
        
        //we only compute the FFT every 64 frame or 2Hz because of the Hamming window
        if(dsp->counter%(W_SIZE/2) == 0){
			fft(dsp,c);
			compute_power_band(dsp,c);
			compute_alpha_power(dsp,c);
			compute_beta_power(dsp,c);
		}
    }
    dsp->counter++;
}

//Compute the mean of the channel 
void mean(emokit_dsp* dsp, int channel){
	dsp->mean[channel] = 0;
	int i;
	for(i=0; i<W_SIZE; i++){
		dsp->mean[channel] += dsp->value[channel][i]/(1.0*W_SIZE);
	}
}

//compute the power in every band of 1Hz
void compute_power_band(emokit_dsp* dsp, int channel){
	int j;
	for(j=0; j<W_SIZE; j++){
		dsp->band_power[channel][j][dsp->counter%HISTORY] = (dsp->f_channels[channel])[j][0]*(dsp->f_channels[channel])[j][0]+(dsp->f_channels[channel])[j][1]*(dsp->f_channels[channel])[j][1];
	}
}

//compute the alpha power 8-12 HZ
void compute_alpha_power(emokit_dsp* dsp, int channel){
		dsp->alpha_power[channel][dsp->counter%HISTORY] = compute_power_band_wave(dsp, channel, ALPHA_START, ALPHA_END);
}

//compute the beta power 16-24Hz
void compute_beta_power(emokit_dsp* dsp, int channel){
	dsp->beta_power[channel][dsp->counter%HISTORY] = compute_power_band_wave(dsp, channel, BETA_START, BETA_END);
}
