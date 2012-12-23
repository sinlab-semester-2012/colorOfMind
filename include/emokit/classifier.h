#include "emokit.h"
#include <stdlib.h>

#define USED_CHANNELS 5
#define WINDOW 128

typedef struct{
	int value[USED_CHANNELS][WINDOW];
	int mean[USED_CHANNELS];
	int var[USED_CHANNELS];
	int max_value[USED_CHANNELS];
	int min_value[USED_CHANNELS];
	double gain[USED_CHANNELS];
} classifier;

void classify_frame(classifier*,struct emokit_frame);
void compute_mean(classifier*,struct emokit_frame, int channel);
void compute_var(classifier*,struct emokit_frame);
void set_max_value(classifier*,struct emokit_frame);
void set_min_value(classifier*,struct emokit_frame);
void lin_reg(classifier*,struct emokit_frame);
