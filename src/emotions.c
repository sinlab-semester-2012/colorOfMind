#include "emokit/emotions.h"

emotions* init_emotions(emokit_dsp* dsp){
	emotions* e;
	e = malloc(sizeof(emotions));
	e->dsp = dsp;
	e->max_diff_arousal=0.35;
	e->max_diff_valence=0.35;
	return e;
}

void compute_arousal(emotions* e){
	compute_average_arousal(e);
	if(fabs(e->arousal_4s-e->arousal_20s) > e->max_diff_arousal)
		e->max_diff_arousal = fabs(e->arousal_4s-e->arousal_20s);
	e->arousal = (e->arousal_4s-e->arousal_20s)/e->max_diff_arousal;
}
void compute_average_arousal(emotions* e){
	int i;
	e->arousal_4s = 0;
	e->arousal_20s = 0;
	//arousal = (F3_alpha/F3_beta + F4_alpha/F4_beta)/2
	for(i=0; i<4*FS/INTERVAL; i++){
		if(e->dsp->beta_power[CHANNEL_AROUSAL_1][i] != 0 && e->dsp->beta_power[CHANNEL_AROUSAL_2][i] != 0)
			e->arousal_4s += ((e->dsp->alpha_power[CHANNEL_AROUSAL_1][i]/e->dsp->beta_power[CHANNEL_AROUSAL_1][i] + e->dsp->alpha_power[CHANNEL_AROUSAL_2][i]/e->dsp->beta_power[CHANNEL_AROUSAL_2][i])/2)/(4*FS/INTERVAL);
	}
	for(i=0; i<20*FS/INTERVAL; i++){
		if(e->dsp->beta_power[CHANNEL_AROUSAL_1][i] != 0 && e->dsp->beta_power[CHANNEL_AROUSAL_2][i] != 0)
			e->arousal_20s += ((e->dsp->alpha_power[CHANNEL_AROUSAL_1][i]/e->dsp->beta_power[CHANNEL_AROUSAL_1][i] + e->dsp->alpha_power[CHANNEL_AROUSAL_2][i]/e->dsp->beta_power[CHANNEL_AROUSAL_2][i])/2)/(20*FS/INTERVAL);
	}
	
}

//TODO: still unstable
void compute_valence(emotions* e){
	compute_average_valence(e);
	if(fabs(e->valence_4s-e->valence_20s) > e->max_diff_valence)
		e->max_diff_valence = fabs(e->valence_4s-e->valence_20s);
	e->valence = (e->valence_4s - e->valence_20s)/e->max_diff_valence;
}

void compute_average_valence(emotions* e){
	int i;
	e->valence_4s = 0;
	e->valence_20s = 0;
	//Using bipolar mesure : AF4-F4, AF3-F3
	//valence = F4-AF4_alpha/F4-AF4_beta - F3-AF3_alpha/F3-AF3_beta
	for(i=0; i<4*FS/INTERVAL; i++){
		if(e->dsp->beta_power[CHANNEL_VAL_1][i] != 0 || e->dsp->beta_power[CHANNEL_VAL_2][i]  != 0)
			e->valence_4s += (e->dsp->alpha_power[CHANNEL_VAL_1][i]/e->dsp->beta_power[CHANNEL_VAL_1][i] - e->dsp->alpha_power[CHANNEL_VAL_2][i]/e->dsp->beta_power[CHANNEL_VAL_2][i])/(4*FS/INTERVAL);
	}
	for(i=0; i<20*FS/INTERVAL; i++){
		if(e->dsp->beta_power[CHANNEL_VAL_1][i] != 0 || e->dsp->beta_power[CHANNEL_VAL_2][i]  != 0)
			e->valence_20s += (e->dsp->alpha_power[CHANNEL_VAL_1][i]/e->dsp->beta_power[CHANNEL_VAL_1][i] - e->dsp->alpha_power[CHANNEL_VAL_2][i]/e->dsp->beta_power[CHANNEL_VAL_2][i])/(20*FS/INTERVAL);
	}
}
