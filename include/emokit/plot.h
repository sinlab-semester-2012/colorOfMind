#include <stdio.h>
#include "emokit_dsp.h"
#include "gnuplot/gnuplot_i.h"

typedef struct{
	emokit_dsp* dsp;
	gnuplot_ctrl * h;
	double band_power[NB_CHANNEL][W_SIZE][HISTORY];
	double average_fourier[NB_CHANNEL][W_SIZE];
	
	
} plot;

plot* init_plot(emokit_dsp* dsp);

void plot_average_fourier();
void plot_fourier();
void plot_reset(plot* p);
void plot_close(plot* p);
