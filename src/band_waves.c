//TODO : Initialize value to predefined numbers so we don't have to wait for the filter to stabilize
//TODO : use is_channel_on to use only relevant channel

#include "../lib/emokit/band_waves.h"

//Create the structure and gives back a pointer to it
waves* new_waves(){	
    waves* w = (waves*)malloc(sizeof(waves));
	initializeTables(w);
	initialize_channels(w);
    return w;
}

//Apply the filter to all channels
void compute_band_waves(waves* w, struct emokit_frame* current_frame, int type){
	
	process_new_frame(w,current_frame);
	
	if(type == ALPHA){
		butterworth_filter_order4(w,coefficients_alpha);
	} 
	else if (type == BETA){
		butterworth_filter_order4(w,coefficients_min_beta);
	} 
	else if (type == MINBETA){
		butterworth_filter_order4(w,coefficients_beta);
	} 
	else {
		printf("Error : Wrong 3rd argument in function compute_band_waves, no such filter");
		return;
	}	
	
	average_of_squares(w);
	average_epoch(w);
}

//BUTTERWORTH BANDPASS FILTER of order 4
void butterworth_filter_order4(waves* w, double coef[2][9]){
	int i,j;
	//For each channel
	for(i=0;i<14;i++){
		//For each coefficients of specified filter
		for(j=0;j<9;j++){
			w->filtered_channels[i][0] += (coef[0][j] * w->channels[i][j]) + (coef[1][j] * w->filtered_channels[i][j]);
		}
	}
}

//Process each new frame
//Called each time we need to get a frame's value
void process_new_frame(waves* w, struct emokit_frame* current_frame){
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
	double value=0.0;
	for(i=0; i<14;i++){
	    for(j=0; j<EPOCH_SIZE; j++){
			value+= w->filtered_channels[i][j]*w->filtered_channels[i][j];
	    }
	    w->epoch_values[i][0]=value/((double)EPOCH_SIZE);
	}
}

//Average the last 4 epoching value
void average_epoch(waves* w){
	int i,j;
	double average;
	for(i=0; i<14;i++){
	    for(j=0; j<EPOCH_AVERAGE; j++){
			average+= w->epoch_values[i][j];
	    }
	    w->averaged_epoch[i]=average/((double)EPOCH_AVERAGE);
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

//take 128 packets to be sure contact_quality values are updated
//if used must make sure this function is called
void initialize_channels(waves* w){
	int i=0;
	for(i=0; i<NB_CHANNELS; i++){
		w->is_channel_on[i] = 1;
	}
}

//take 128 packets to be sure contact_quality values are updated
void auto_setup_channel(waves* w,emokit_device* d){
	int i=0;
	
	for(i=0; i<128; i++){
		emokit_get_next_frame(d);
	}
	for(i=0; i<NB_CHANNELS; i++){
		if(d->contact_quality[i] == 0){
			w->is_channel_on[i] = 0;
		}
	}
}

//setup channel according to a definite table
//You should call the auto_setup_channel if you want to remove automatically unconfigured channels
void manual_setup_channel(waves* w,int table[NB_CHANNELS]){
	int i=0;
	for(i=0; i<NB_CHANNELS; i++){
		if(table[i] == 0){
			w->is_channel_on[i] = 0;
		}
	}
}

//Initialize tables to zero
void initializeTables(waves* w){
    memset(w->channels, 0, sizeof w->channels);
    memset(w->filtered_channels, 0, sizeof w->filtered_channels);
    memset(w->epoch_values, 0, sizeof w->epoch_values);
}

//Free the memory
void deleteWaves(waves * w){
	free(w);
}
