//TODO : average 4 last epoc

#include "../lib/emokit/band_waves.h"


waves* new_waves()
{	
    waves* w = (waves*)malloc(sizeof(waves));
    return w;
}

void compute_band_waves(waves* w, struct emokit_frame* current_frame, int type){
	process_new_frame(w,current_frame);
	if(type == 1){
		butterworth_filter_order4(w,coefficients_alpha);
	} 
	else if (type == 2){
		butterworth_filter_order4(w,coefficients_min_beta);
	} 
	else if (type == 3){
		butterworth_filter_order4(w,coefficients_beta);
	} 
	else {
		printf("Error : Wrong 3rd argument in function compute_band_waves, no such filter");
		return;
	}	
	average_of_squares(w);
}

//BUTTERWORTH FILTER of order 4
void butterworth_filter_order4(waves* w, double coef[2][9]){
	int i,j;
	//For each channel
	for(i=0;i<14;i++){
		//For each coefficient of filter
		for(j=0;j<9;j++){
			w->filtered_channels[i][0] += (coef[0][j] * w->channels[i][j]) + (coef[1][j] * w->filtered_channels[i][j]);
		}
	}
}

void process_new_frame(waves* w, struct emokit_frame* current_frame)
{
    //Make an array to copy the values into and access sequentially
    int frame_vals[14];

    frame_vals[0]  = current_frame->F3;
	frame_vals[1]  = current_frame->FC6;
	frame_vals[2]  = current_frame->P7;
	frame_vals[3]  = current_frame->T8;
	frame_vals[4]  = current_frame->F7;
	frame_vals[5]  = current_frame->F8;
	frame_vals[6]  = current_frame->T7;
	frame_vals[7]  = current_frame->P8;
	frame_vals[8]  = current_frame->AF4;
	frame_vals[9]  = current_frame->F4;
	frame_vals[10] = current_frame->AF3;
	frame_vals[11] = current_frame->O2;
	frame_vals[12] = current_frame->O1;
	frame_vals[13] = current_frame->FC5;

    //Shift all the arrays back
    int f = 0;
    int i = 0;
    for(f=0;f<14;f++)
    {

        //Shift all the frames back
        for(i=1;i<EPOCH_SIZE;i++)
        {
            w->channels[f][i] = w->channels[f][i-1];
			w->filtered_channels[f][i] = w->filtered_channels[f][i-1];
        }
        
        //Save the new value
		//new value is between -1 and 1
        w->channels[f][0] = (double)(frame_vals[f]/ GAIN);

		//Shift all the frames back for epoch average
        for(i=1;i<EPOCH_AVERAGE;i++)
        {
            w->epoch_values[f][i] = w->epoch_values[f][i-1];
        }
        
        //new value 0 for filter at time 0
        w->filtered_channels[f][0] = 0;
    }
    

}

//get the average of the squared signals
void average_of_squares(waves* w){
	int i,j;
	double f=0.0;
	for(i=0; i<14;i++){
	    for(j=0; j<EPOCH_SIZE; j++){
		f+= w->filtered_channels[i][j]*w->filtered_channels[i][j];
	    }
	    w->epoch_values[i][0]=f/((double)EPOCH_SIZE);
	}
}

//crop high and low value according to MAX and MIN values
void crop(waves* w){
	int i;
	
	for(i=0; i<14;i++){
		if(w->epoch_values[i][0]>CROP_MAX){
			w->epoch_values[i][0] =CROP_MAX;
		}
		else if(w->epoch_values[i][0]<CROP_MIN){
			w->epoch_values[i][0]=CROP_MIN;
		}
	}	
}

//Center the signal
void center(waves* w){
	int i;
	for(i=0; i<14;i++){
	    w->epoch_values[i][0] -=CROP_CENTER;
	}
}
