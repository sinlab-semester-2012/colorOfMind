#include "emokit/plot.h"

plot* init_plot(emokit_dsp* dsp){
		
	plot* p;
	p=malloc(sizeof(plot));	
	p->dsp = dsp;
	//init GNUPLOT
	p->h = gnuplot_init();
    gnuplot_setstyle(p->h,"lines");
    gnuplot_set_xlabel(p->h, "Frequency") ;
    gnuplot_set_xlabel(p->h, "Magnitude") ;
    return p;
}

//TODO: do the update everytime, not just when function is called 
void plot_average_fourier(plot* p){
	int i,j,k;
	//for each channel
	for(i=0; i<NB_CHANNEL; i++){
		for(j=0; j<W_SIZE; j++){
			p->average_fourier[i][j] = 0;
			//for each value last HISTORY values
			for(k=0; k<HISTORY; k++){
				p->average_fourier[i][j] += p->band_power[i][j][k]/HISTORY;
			}
		}
	}
	
	gnuplot_plot_x(p->h, p->average_fourier[0], 32, "F3") ;
	gnuplot_plot_x(p->h, p->average_fourier[1], 32, "F4") ;
	gnuplot_plot_x(p->h, p->average_fourier[2], 32, "AF3") ;
	gnuplot_plot_x(p->h, p->average_fourier[3], 32, "AF4") ;
	gnuplot_plot_x(p->h, p->average_fourier[4], 32, "O2") ;

}

//TODO : plot the correct value : not the 32 last value of a certain frequency
void plot_fourier(plot* p){
	gnuplot_plot_x(p->h, p->dsp->band_power[0][0], 32, "F3");
	gnuplot_plot_x(p->h, p->dsp->band_power[0][1], 32, "F4") ;
	gnuplot_plot_x(p->h, p->dsp->band_power[0][2], 32, "AF3") ;
	gnuplot_plot_x(p->h, p->dsp->band_power[0][3], 32, "AF4") ;
	gnuplot_plot_x(p->h, p->dsp->band_power[0][4], 32, "O2") ;
}

void plot_reset(plot* p){
	gnuplot_resetplot(p->h);
}

void plot_close(plot* p){
	gnuplot_close(p->h);
	free(p);
}
