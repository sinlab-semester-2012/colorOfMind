#include "emokit.h"
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define W_SIZE 1000
#define MAX_SENSOR_VALUE 8192
#define HISTORY 200

//Name the sensor we need : F3,F4,AF3,AF4
#define F3_sensor 0
#define F4_sensor 1
#define AF3_sensor 2
#define AF4_sensor 3

//Start and end of band waves of interest
#define ALPHA_START 8
#define ALPHA_END 12
#define BETA_START 16
#define BETA_END 24

typedef struct
{
    //Channel history
    fftw_complex channels[4][W_SIZE];
    //high pass filtered channel
    fftw_complex filtered_channels[4][W_SIZE];
    //Channel fourier transform
    fftw_complex f_channels[4][W_SIZE];

	double band_power[4][W_SIZE];
    //alpha band channels power
    double alpha_power[4][HISTORY];
    //beta band channels power
    double beta_power[4][HISTORY];
    
    double average_alpha_power[4];
    double average_beta_power[4];
   
    //Array to save the input to fftw
    fftw_complex windowed[W_SIZE];
    //Window function coefficients
    double window[W_SIZE];

    //int beginning_tab;
    //int count;

} emokit_dsp;


emokit_dsp* emokit_dsp_create();
int emokit_dsp_free(emokit_dsp* dsp);
void fft(emokit_dsp* dsp, int channel);
void free_fft(emokit_dsp* dsp);
void hamming_window(double* w);
void flat_top_window(double* window);
void low_pass();
double compute_power_band_wave(emokit_dsp* dsp, int channel, int start, int end);
void compute_frame(emokit_dsp* s, struct emokit_frame f);


#ifdef __cplusplus
};
#endif
