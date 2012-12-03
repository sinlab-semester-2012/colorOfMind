#include "emokit/classifier.h"

void classify_frame(classifier* c, struct emokit_frame f){
	compute_mean(c,f);
	set_max_value(c,f);
	set_min_value(c,f);
}

void compute_mean(classifier* c,struct emokit_frame f){
	int i;
	for(i=0; i<USED_CHANNELS; i++){
		//IIR filter 1st order
		//For K = 8. αmin = 0.1533333
		//For K = 16. αmin = 0.08
		//For K = 24. αmin = 0.0533333
		//For K = 32. αmin = 0.04
		//For K = 40. αmin = 0.0333333
		//For K = 48. αmin = 0.0266667
		//For K = 56. αmin = 0.0233333
		//For K = 64. αmin = 0.02
		//For K = 72. αmin = 0.0166667
		c->mean[i] = 0.04*f.F3 + 0.96*c->mean[i];
	}
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
