#include <stdio.h>
#include <math.h>
#include "emokit_dsp.h"
#include "emotions.h"
#include "gnuplot/gnuplot_i.h"


typedef struct{
	emokit_dsp* dsp;
	gnuplot_ctrl * h;
	emotions* e;
	//double band_power[NB_CHANNEL][W_SIZE][HISTORY];
	double average_fourier[NB_CHANNEL][W_SIZE];
	
	double arousal[HISTORY];
	double valence[HISTORY];
} plot;

plot* init_plot(emokit_dsp* dsp, emotions* e);
void plot_average_fourier(plot* p);
void plot_arousal(plot* p);
void plot_valence(plot* p);
void plot_reset(plot* p);
void plot_close(plot* p);
void shift_table(double t[HISTORY], int channel, int size);
