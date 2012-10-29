#include "emokit.h"
#include <stdlib.h>
#include <stdio.h>

#define EPOC_HLF 8192
#define EPOCH_SIZE 128
#define EPOCH_AVERAGE 4

//needs calibration
#define CROP_MAX -1
#define CROP_MIN 1
#define CROP_CENTER 0

#define ALPHA 1
#define MINBETA 2
#define BETA 3

#define GAIN 1.374144519e+04



typedef struct
{   
    //Channel history
    double channels[14][EPOCH_SIZE];
	//filtered channel
    double filtered_channels[14][EPOCH_SIZE];
	//value after epoching
    double epoch_values[14][EPOCH_AVERAGE];
    double averaged_epoch[14];
    
    int is_channel_on[14];
    
} waves;

//Bandpass Butterworth filter 8-12Hz (alpha waveswith filter order 4
//{x coefficient, y coefficient}
double coefficients_alpha[2][9] = {{1.0,0.0,-4.0,0.0,6.0,0.0,-4.0,0.0,1.0},
{0.0,6.6351660481,-20.0194593593,35.7361014123,-41.2116361169, 31.4237123835,-15.4796097211,4.5117145602, -0.5980652616}};
//Bandpass Butterworth filter 16-24Hz with filter order 4
double coefficients_beta[2][9] = {{1.0,0.0,-4.0,0.0,6.0,0.0,-4.0,0.0,1.0},
{0.0,3.9520648501,-8.8657337188,12.8548510907,-13.3819647057, 9.9299835533,-5.2881194347,1.8174217460,-0.3555773823}};
//Bandpass Butterworth filter 12-16Hz with filter order 4
double coefficients_min_beta[2][9] = {{1.0,0.0,-4.0,0.0,6.0,0.0,-4.0,0.0,1.0},
{0.0,5.8157716820,-16.1883828721, 27.5996290071,-31.3663305138,24.2699601896,-12.5178696263,3.9545508864,-0.5980652616}};


//FUNCTIONS

waves* new_waves();
void compute_band_waves(waves*, struct emokit_frame*, int);
void butterworth_filter_order4(waves*, double tab[2][9]);
void process_new_frame(waves*, struct emokit_frame*);
void average_of_squares(waves*);
void crop(waves*);
void center(waves*);
void initializeTables(waves*);
void initialize_channels(waves*);
void auto_setup_channels(waves*, emokit_device*);
void manual_setup_channel(waves*,int table[NB_CHANNELS]);
void deleteWaves(waves*);
