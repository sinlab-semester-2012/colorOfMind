#ifndef LIBEMOKIT_DSP_H_
#define LIBEMOKIT_DSP_H_

#include "emokit.h"
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

//sampling frequency in Hz
#define FS 128
//window size
#define W_SIZE 128
//max value from sensor (-8192 ; 8192)
#define MAX_SENSOR_VALUE 8192
//Number of value conserved as history for averaging
#define HISTORY 100

//number of frame between every FFT
#define INTERVAL 64

//number channel used
#define NB_CHANNEL 4
//Name the sensor we need : F3,F4,AF3,AF4
#define F3_SENSOR 0
#define F4_SENSOR 1
//bipolar sensor using the F3, F4 as references
#define F3AF3 2
#define F4AF4 3

//Start and end of band waves of interest : Alpha and Beta
#define ALPHA_START 7
#define ALPHA_END 12
#define BETA_START 16
#define BETA_END 24


typedef struct
{
    //Channel history
    fftw_complex channels[NB_CHANNEL][W_SIZE];
    //Channel fourier transform
    fftw_complex f_channels[NB_CHANNEL][W_SIZE];
	//high pass filtered channel
    fftw_complex filtered_channels[NB_CHANNEL][W_SIZE];

	double band_power[NB_CHANNEL][W_SIZE][HISTORY];
    //alpha band channels power
    double alpha_power[NB_CHANNEL][HISTORY];
    //beta band channels power
    double beta_power[NB_CHANNEL][HISTORY];

    //Array to save the input to fftw
    fftw_complex windowed[W_SIZE];
    //Window function coefficients
    double window[W_SIZE];
    
    //Store the last W_SIZE raw values
    int value[NB_CHANNEL][W_SIZE];
    double mean[NB_CHANNEL];
    
    int counter;
} emokit_dsp;


emokit_dsp* emokit_dsp_create();
int emokit_dsp_free(emokit_dsp* dsp);

//FFT
void fft(emokit_dsp* dsp, int channel);
void free_fft(emokit_dsp* dsp);

//windows
void hamming_window(double* w);
void flat_top_window(double* window);
void no_window(double* w);
void mean(emokit_dsp*, int);

//Power computation
double compute_power_band_wave(emokit_dsp* dsp, int channel, int start, int end);
void compute_frame(emokit_dsp* s, struct emokit_frame f);
void compute_power_band(emokit_dsp* dsp, int channel);
void compute_alpha_power(emokit_dsp* dsp, int channel);
void compute_beta_power(emokit_dsp* dsp, int channel);


#ifdef __cplusplus
};
#endif

#endif //LIBEMOKIT_H_
