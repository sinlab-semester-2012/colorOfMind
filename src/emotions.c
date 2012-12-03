#include "emokit/emotions.h"

emotions* init_emotion(emokit_dsp* dsp){
	emotions* e;
	e = malloc(sizeof(emotions));
	e->dsp = dsp;
	return e;
}

void compute_arousal(emotions* e){
	e->arousal = (e->arousal_4s-e->arousal_20s)/abs(e->arousal_4s-e->arousal_20s);
}
void compute_average_arousal(emotions* e){
	int i;
	for(i=0; i<4*INTERVAL/FS; i++){
		e->arousal_4s += (e->dsp->alpha_power[CHANNEL_AROUSAL][i]/e->dsp->beta_power[CHANNEL_AROUSAL][i])/(4*INTERVAL/FS);
	}
	for(i=0; i<20*INTERVAL/FS; i++){
		e->arousal_20s += (e->dsp->alpha_power[CHANNEL_AROUSAL][i]/e->dsp->beta_power[CHANNEL_AROUSAL][i])/(20*INTERVAL/FS);
	}
	
}

void compute_valence(emotions* e){
	e->valence = (e->valence_4s-e->valence_20s)/abs(e->valence_4s-e->valence_20s);
}
void compute_average_valence(emotions* e){
	int i;
	for(i=0; i<4*INTERVAL/FS; i++){
		e->valence_4s += (e->dsp->alpha_power[CHANNEL_VAL_1][i]/e->dsp->beta_power[CHANNEL_VAL_1][i] - e->dsp->alpha_power[CHANNEL_VAL_2][i]/e->dsp->beta_power[CHANNEL_VAL_2][i])/(4*INTERVAL/FS);
	}
	for(i=0; i<20*INTERVAL/FS; i++){
		e->valence_20s += (e->dsp->alpha_power[CHANNEL_VAL_1][i]/e->dsp->beta_power[CHANNEL_VAL_1][i] - e->dsp->alpha_power[CHANNEL_VAL_2][i]/e->dsp->beta_power[CHANNEL_VAL_2][i])/(20*INTERVAL/FS);
	}
}
