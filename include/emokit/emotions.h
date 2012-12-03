#include <stdio.h>
#include <math.h>
#include "emokit.h"
#include "emokit_dsp.h"

#define CHANNEL_AROUSAL 1
#define CHANNEL_VAL_1 2
#define CHANNEL_VAL_2 3

typedef struct{
	emokit_dsp* dsp;
	
	double arousal;
	double arousal_4s;
	double arousal_20s;
	
	double valence;
	double valence_4s;
	double valence_20s;
	
} emotions;

emotions* init_emotions();

void compute_arousal(emotions* e);
void compute_average_arousal(emotions* e);

void compute_valence(emotions* e);
void compute_average_valence(emotions* e);




