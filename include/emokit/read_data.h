#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "emokit.h"

typedef struct
{   
    char* name;
    FILE* fichier;
    unsigned int nbSamples;
    unsigned int readingCursor;
    int play;
} data;

#ifdef __cplusplus
extern "C"
{
#endif
data* new_data(char*, unsigned int);
int open_data_file(data*);
int check_file_opening(FILE*);
struct emokit_frame data_get_next_frame(data*);
int close_data(data*);

#ifdef __cplusplus
};
#endif

