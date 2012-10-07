#include "emokit.h"
//#include <math.h>
#include <stdlib.h>


#define EPOCH_SIZE 128
#define EPOCH_AVERAGE 4
#define CROP_MAX -1
#define CROP_MIN 1
#define CROP_CENTER 0

typedef struct
{   
    //Channel history
    double channels[14][EPOCH_SIZE];
    //Channel fourier transform 
    double filtered_channels[14][EPOCH_SIZE];
    double epoch_values[14][EPOCH_AVERAGE];
    //double final_values[14]

    double coefficients_alpha[2][8];
    double coefficients_beta[2][8];
    double coefficients_low_beta[2][8];
    
} waves;


