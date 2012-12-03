#include <stdio.h>
#include "emotion.h"

typedef struct {
	int red;
	int green;
	int blue;
	int alpha;
	emotions* e;
} light;

light* init_light(emotions* e);
void update_color(light* l);
void compute_color(light* l);
void compute_alpha(light* l);

