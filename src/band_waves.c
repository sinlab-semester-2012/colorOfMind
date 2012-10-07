//BUTTERWORTH FILTER for 8-12HZ with order 4
void processButterworthAlphaWaves(struct waves* w){
	int i,j;
	for(i=0; i<14; i++){
		for(j=1;j<9;j++){
			w->butterworth_channels[i][j][0] = w->butterworth_channels[i][j][0];
		}
	}
	for(i=0; i<14; i++){
		w->butterworth_channels[0][i][0] = 
			(1 * (w->channels)[i][8][0])
		     + (  0. * (w->channels)[i][7][0])
		     + ( -4. * (w->channels)[i][6][0])
		     + (  0. * (w->channels)[i][5][0])
		     + (  6. * (w->channels)[i][4][0])
		     + (  0. * (w->channels)[i][3][0])
		     + ( -4. * (w->channels)[i][2][0])
		     + (  0. * (w->channels)[i][1][0])
		     + (  1. * (w->channels)[i][0][0])

		     + ( -0.5980652616 * w->butterworth_channels[i][8][0])
		     + (  4.5117145602 * w->butterworth_channels[i][7][0])
		     + (-15.4796097211 * w->butterworth_channels[i][6][0])
		     + ( 31.4237123835 * w->butterworth_channels[i][5][0])
		     + (-41.2116361169 * w->butterworth_channels[i][4][0])
		     + ( 35.7361014123 * w->butterworth_channels[i][3][0])
		     + (-20.0194593593 * w->butterworth_channels[i][2][0])
		     + (  6.6351660481 * w->butterworth_channels[i][1][0]);
	}
}

void process_frame(struct waves* w, struct emokit_frame* current_frame)
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
        for(i=1<i;i<EPOCH_SIZE;i++)
        {
            w->channels[f][i] = w->channels[f][i-1];
	    w->filtered_channels[f][i] = w->filtered_channels[f][i];
        }
        //Save the new value
	//new value is between -1 and 1
        w->channels[f][0] = ((double)(frame_vals[f]-EPOC_HLF))/(double)EPOC_HLF;

	//Shift all the frames back for epoch average
        for(i=1<i;i<EPOCH_AVERAGE;i++)
        {
            w->epoch_values[f][i] = w->epoch_values[f][i-1];
        }
    }
    

}

//get the average of the squared signals
void average_of_squares(waves* w){
	int i,j;
	int 
	for(i=0; i<14;i++){
	    for(j=0; j<EPOCH_SIZE; j++){
		w->epoch_values[i][0] += w_>filtered_channels[i][0]*w_>filtered_channels[i][0];
	    }
	    w->epoch_values[i][0]=w->epoch_values[i][0]/((double)EPOCH_SIZE);
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
