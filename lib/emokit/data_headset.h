#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{   
    char* name;
    FILE* fichier;
    unsigned int nbSamples;
    unsigned int readingCursor;
} data;

#ifdef __cplusplus
extern "C"
{
#endif
data* new_data(char*, unsigned int);
int createDataFile(data*);
int openDataFile(data*);
int checkFileOpening(FILE*);
int writeData(data*, emokit_device*);
int data_get_next_frame(data*, emokit_device*);
int closeFile(FILE*);

#ifdef __cplusplus
};
#endif

