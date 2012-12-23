#include "emokit/classifier.h"

void classify_frame(classifier* c, struct emokit_frame f){
	int i=0;
	for(i=0; i<USED_CHANNELS;i++){
		compute_mean(c,f,i);
	}
	set_max_value(c,f);
	set_min_value(c,f);
}

void compute_mean(classifier* c,struct emokit_frame f, int channel){
	c->mean[channel] = 0;
	int i;
	for(i=0; i<WINDOW; i++){
		c->mean[channel] += c->value[channel][i];
	}
	c->mean[channel] = c->mean[channel] / WINDOW;
}

void compute_var(classifier* c,struct emokit_frame f);
//E[X²]- E[X]²

void set_max_value(classifier* c,struct emokit_frame f){
	int i;
	for(i=0; i<USED_CHANNELS; i++){
		c->max_value[i] = c->mean[i]*1.05;
	}
}
void set_min_value(classifier* c,struct emokit_frame f){
	int i;
	for(i=0; i<USED_CHANNELS; i++){
		c->max_value[i] = c->mean[i]*0.95;
	}
}

void lin_reg(classifier*,struct emokit_frame);
