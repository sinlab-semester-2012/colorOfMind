#include "emokit/light.h"

light* init_light(emotions* e);{
	light* l;
	l= malloc(sizeof(light));
	l->e = e;
	return l;
}

void update_data(light* l){
	l->e->valence = 0;
	l->e->arousal = 0;
}


void compute_color(light* l){
	l->red = 0;
	l->blue = 0;
	l->green = 0;
}
void compute_alpha(light* l){
	l->alpha=0;
}

