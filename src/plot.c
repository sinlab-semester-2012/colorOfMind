#include "emokit/plot.h"

plot* init_plot(emokit_dsp* dsp, emotions* e){
		
	plot* p;
	p=malloc(sizeof(plot));	
	p->dsp = dsp;
	p->e = e;
	//init GNUPLOT
	p->h = gnuplot_init();
    gnuplot_setstyle(p->h,"lines");
    gnuplot_set_xlabel(p->h, "Frequency") ;
    gnuplot_set_xlabel(p->h, "Magnitude") ;
    return p;
}

void plot_average_fourier(plot* p){
	int i,j,k;
	//for each channel
	for(i=0; i<NB_CHANNEL; i++){
		for(j=0; j<W_SIZE; j++){
			p->average_fourier[i][j] = 0;
			//for each value last HISTORY values
			for(k=0; k<HISTORY; k++){
				p->average_fourier[i][j] += p->dsp->band_power[i][j][k]/HISTORY;
			}
			p->average_fourier[i][j] = log(p->average_fourier[i][j]);
		}
	}
	
	gnuplot_plot_x(p->h, p->average_fourier[0], 32, "F3") ;
	gnuplot_plot_x(p->h, p->average_fourier[1], 32, "F4") ;
	gnuplot_plot_x(p->h, p->average_fourier[2], 32, "AF3") ;
	gnuplot_plot_x(p->h, p->average_fourier[3], 32, "AF4") ;
}

void plot_arousal(plot* p){
	shift_table(p->arousal, 1, HISTORY);
	p->arousal[0] = p->e->arousal;
	gnuplot_plot_x(p->h, p->arousal, HISTORY, "Arousal");
}

void plot_valence(plot* p){
	shift_table(p->valence, 1, HISTORY);
	p->valence[0] = p->e->valence;
	gnuplot_plot_x(p->h, p->valence, HISTORY, "Valence");
}

void plot_reset(plot* p){
	gnuplot_resetplot(p->h);
}

void plot_close(plot* p){
	gnuplot_close(p->h);
	free(p);
}

void shift_table(double t[HISTORY], int channels, int size){
	int i,j=0;
	for(j=0; j<channels; j++){
		for(i=size-2; i>=0; i--){
			t[i+1] = t[i];
		}
	}
}
