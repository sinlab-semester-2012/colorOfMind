#ifndef LIBEMOTION_H_
#define LIBEMOTION_H_

#include <stdio.h>
#include <math.h>
#include "emokit.h"
#include "emokit_dsp.h"

//correpond to both sensor the closest to Fpz : F3, F4
#define CHANNEL_AROUSAL_1 1
#define CHANNEL_AROUSAL_2 2
//correspond to the right hemisphere bipolar sensor (F4-AF4)
#define CHANNEL_VAL_1 3
//correspond to the left hemisphere bipolar sensor (F3-AF3)
#define CHANNEL_VAL_2 2

typedef struct{
	emokit_dsp* dsp;
	
	double arousal;
	double arousal_4s;
	double arousal_20s;
	double max_diff_arousal;
	
	double valence;
	double valence_4s;
	double valence_20s;
	double max_diff_valence;
	
} emotions;

emotions* init_emotions(emokit_dsp* dsp);

void compute_arousal(emotions* e);
void compute_average_arousal(emotions* e);

void compute_valence(emotions* e);
void compute_average_valence(emotions* e);


#endif //LIBEMTION_H_
