#include "emokit/emokit_dsp.h"	
#include <math.h>

emokit_dsp* emokit_dsp_create()
{
	emokit_dsp* dsp = (emokit_dsp*)malloc(sizeof(emokit_dsp));
	memset(dsp,0,sizeof(emokit_dsp));
	int i,j,k;
	for(i=0; i<NB_CHANNEL; i++){
		for(j=0; j<W_SIZE; j++){
			dsp->channels[i][j][0] = 0;
			dsp->filtered_channels[i][j][0]=0;
			for(k=0; k<HISTORY; k++){
				dsp->band_power[i][j][k]=0;
			}
		}
	}
	
	dsp->cf = (classifier*)malloc(sizeof(classifier));
	
	dsp->counter=0;
	
	//chose window
    no_window(dsp->window);
	//hamming_window(dsp->window);
	
	return dsp;
}

int emokit_dsp_free(emokit_dsp* dsp){
	free(dsp);
}

void fft(emokit_dsp* dsp, int channel){
	fftw_plan p;
	
	//Pointer to the channels data
    //fftw_complex* channelValue = dsp->channels[channel];
    fftw_complex* channelValue = dsp->filtered_channels[channel];

    //Window the measurements 
    int i=0;
    for(i=0;i<W_SIZE;i++)
    {
        dsp->windowed[i][0] = dsp->window[i]*channelValue[i][0];
        //dsp->windowed[i][1] = dsp->window[i]*channelValue[i][1];
    }
 
    //FFT the frame
	p = fftw_plan_dft_1d(W_SIZE, dsp->windowed, dsp->f_channels[channel], FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);

}

void high_pass_filter(emokit_dsp* dsp, int channel){
	//double hp_filter[W_SIZE] = {0.0164033392574522,0.000408486918091996,0.000386113111224557,0.000350800995951998,0.000295800747088937,
	//0.000221751601303867,0.000128878984737222,1.94048586299303e-05,-0.000110736239474338,-0.000259568228201922,-0.000429619908110947,
	//-0.000617887250987437,-0.000827828403942340,-0.00105650377896189,-0.00130666341367854,-0.00157479560398759,-0.00186418265267907,
	//-0.00217129348350810,-0.00249899627259110,-0.00284328620069372,-0.00320740460663446,-0.00358709328196363,-0.00398520009541355,
	//-0.00439692507744105,-0.00482555187501155,-0.00526591285868953,-0.00572107735966985,-0.00618536959428194,-0.00666272190493942,
	//-0.00714695456597673,-0.00764193428445332,-0.00814062416376853,-0.00864841327504208,-0.00915702745705431,-0.00967181292511137,
	//-0.0101822035276680,-0.0106976606503983,-0.0112042156004143,-0.0117127570153077,-0.0121925924718140,-0.0126854294627640,-0.0131800457007999,
	//-0.0136424849177247,-0.0140983834569993,-0.0145414238154211,-0.0149722746711284,-0.0153794504680008,-0.0157705148371049,-0.0161392925169480,
	//-0.0164892372350685,-0.0168138324047041,-0.0171164091442021,-0.0173924257887103,-0.0176440071363469,-0.0178665966078135,-0.0180624672863061,
	//-0.0182282453440531,-0.0183658665573572,-0.0184720752897124,-0.0185491783069559,-0.0185946645143329,0.981389315689471,-0.0185946645143329,
	//-0.0185491783069559,-0.0184720752897124,-0.0183658665573572,-0.0182282453440531,-0.0180624672863061,-0.0178665966078135,-0.0176440071363469,
	//-0.0173924257887103,-0.0171164091442021,-0.0168138324047041,-0.0164892372350685,-0.0161392925169480,-0.0157705148371049,-0.0153794504680008,
	//-0.0149722746711284,-0.0145414238154211,-0.0140983834569993,-0.0136424849177247,-0.0131800457007999,-0.0126854294627640,-0.0121925924718140,
	//-0.0117127570153077,-0.0112042156004143,-0.0106976606503983,-0.0101822035276680,-0.00967181292511137,-0.00915702745705431,-0.00864841327504208,
	//-0.00814062416376853,-0.00764193428445332,-0.00714695456597673,-0.00666272190493942,-0.00618536959428194,-0.00572107735966985,
	//-0.00526591285868953,-0.00482555187501155,-0.00439692507744105,-0.00398520009541355,-0.00358709328196363,-0.00320740460663446,
	//-0.00284328620069372,-0.00249899627259110,-0.00217129348350810,-0.00186418265267907,-0.00157479560398759,-0.00130666341367854,
	//-0.00105650377896189,-0.000827828403942340,-0.000617887250987437,-0.000429619908110947,-0.000259568228201922,-0.000110736239474338,
	//1.94048586299303e-05,0.000128878984737222,0.000221751601303867,0.000295800747088937,0.000350800995951998,0.000386113111224557,
	//0.000408486918091996,0.0164033392574522,0,0,0,0,0};

	
	//double hp_filter [W_SIZE] = {-0.00385868762283253,-0.00107782144276260,-0.00122468893796172,-0.00138185521022985,-0.00154980298954184,-0.00172797313020619,
	//-0.00191702881552113,-0.00211649125453757,-0.00232618092683026,-0.00254694128687305,-0.00277786325978484,-0.00301939562701598,-0.00327111042340514,
	//-0.00353323287415516,-0.00380461687510760,-0.00408567616289047,-0.00437550733231310,-0.00467409404917833,-0.00498028197254051,-0.00529432792575193,
	//-0.00561533519455277,-0.00594342942625157,-0.00627715296248023,-0.00661622907746625,-0.00695911017831665,-0.00730567699232615,-0.00765455509884291,
	//-0.00800636072392475,-0.00835955447959125,-0.00871400131646867,-0.00906708623717752,-0.00941876927135917,-0.00976659883793324,-0.0101133676676832,
	//-0.0104564261546275,-0.0107950724944858,-0.0111223031001360,-0.0114494691694534,-0.0117651094083582,-0.0120722875302192,-0.0123706853991739,
	//-0.0126579104535028,-0.0129340169142264,-0.0131974219252010,-0.0134492397226211,-0.0136854438819604,-0.0139087151700663,-0.0141161788160537,
	//-0.0143081340071345,-0.0144827893162376,-0.0146416974167753,-0.0147827486708167,-0.0149062936130737,-0.0150108050472428,-0.0150971662073972,
	//-0.0151642598659809,-0.0152128998899536,-0.0152418652749548,0.984748162817975,-0.0152418652749548,-0.0152128998899536,-0.0151642598659809,
	//-0.0150971662073972,-0.0150108050472428,-0.0149062936130737,-0.0147827486708167,-0.0146416974167753,-0.0144827893162376,-0.0143081340071345,
	//-0.0141161788160537,-0.0139087151700663,-0.0136854438819604,-0.0134492397226211,-0.0131974219252010,-0.0129340169142264,-0.0126579104535028,
	//-0.0123706853991739,-0.0120722875302192,-0.0117651094083582,-0.0114494691694534,-0.0111223031001360,-0.0107950724944858,-0.0104564261546275,
	//-0.0101133676676832,-0.00976659883793324,-0.00941876927135917,-0.00906708623717752,-0.00871400131646867,-0.00835955447959125,
	//-0.00800636072392475,-0.00765455509884291,-0.00730567699232615,-0.00695911017831665,-0.00661622907746625,-0.00627715296248023,
	//-0.00594342942625157,-0.00561533519455277,-0.00529432792575193,-0.00498028197254051,-0.00467409404917833,-0.00437550733231310,
	//-0.00408567616289047,-0.00380461687510760,-0.00353323287415516,-0.00327111042340514,-0.00301939562701598,-0.00277786325978484,
	//-0.00254694128687305,-0.00232618092683026,-0.00211649125453757,-0.00191702881552113,-0.00172797313020619,-0.00154980298954184,
	//-0.00138185521022985,-0.00122468893796172,-0.00107782144276260,-0.00385868762283253, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//int i;
	//dsp->filtered_channels[channel][W_SIZE-1][0] = 0;
	//for(i=0; i<W_SIZE-1; i++){
		//dsp->filtered_channels[channel][W_SIZE-1][0] += hp_filter[i]*dsp->channels[channel][W_SIZE-2-i][0];
		//printf("%e\n", dsp->filtered_channels[channel][W_SIZE-1][0]);
	//}
	dsp->filtered_channels[channel][W_SIZE-1][0] = dsp->channels[channel][W_SIZE-1][0];
}

void free_fft(emokit_dsp* dsp){
	int i;
	for(i=0; i<NB_CHANNEL; i++){
		free(dsp->channels[i]); 
		free(dsp->f_channels[i]);
	}
}

void hamming_window(double* w){
	int i = 0;
    for(i=0;i<W_SIZE;i++)
        *(w+i) = 0.54 - 0.46*cos(2*M_PI*((double)i/(W_SIZE+1)));
}

void flat_top_window(double* w){
	int j = 0;
    for(j=0;j<W_SIZE;j++)
		*(w+j) = 1-1.93*cos(2*M_PI*((double)j/(W_SIZE+1)))+1.29*cos(4*M_PI*((double)j/(W_SIZE+1)))-0.388*cos(6*M_PI*((double)j/(W_SIZE+1)))+0.032*cos(8*M_PI*((double)j/(W_SIZE+1)));
}

void no_window(double* w){
	int i=0;
    for(i=0;i<W_SIZE;i++)
    {
        *(w+i) = 1;
    }
}

double compute_power_band_wave(emokit_dsp* dsp, int channel, int f_start, int f_end){
	int j=0;
	//frequency = k/T, where T is your total sampling period (T=1/128*W_SIZE = 1sec)
	//The frequency k/n is the same as the frequency (n-k)/n - Only one entry for k=0 and k=n/2

	long double power = 0;
	int start = floor(f_start*(W_SIZE/2)/64);
	int end = ceil(f_end*(W_SIZE/2)/64);
	for(j=start; j<=end; j++){
		power += (dsp->f_channels[channel][j][0]*dsp->f_channels[channel][j][0]+dsp->f_channels[channel][j][1]*dsp->f_channels[channel][j][1]);
		power += (dsp->f_channels[channel][W_SIZE-j][0]*dsp->f_channels[channel][W_SIZE-j][0]+dsp->f_channels[channel][W_SIZE-j][1]*dsp->f_channels[channel][W_SIZE-j][1]);
    }
    return (double)power;
}

void compute_frame(emokit_dsp* dsp, struct emokit_frame frame){
	int c;
	//classify_frame(dsp->cf, frame);
	for(c=0;c<NB_CHANNEL;c++)
    {
        //Shift all the frames back
        int i;
        for(i=1;i<W_SIZE;i++)
        {
            (dsp->channels[c])[i-1][0] = (dsp->channels[c])[i][0];
            (dsp->filtered_channels[c])[i-1][0] = (dsp->channels[c])[i][0];
        }
        //Check if value of sensor are correct using the min-max bound given by the classifier
        
        //we update the NB_CHANNEL sensor - value is set between -1 and 1
        switch(c){
			case F3_SENSOR:
				//frame.F3 = min(dsp->cf->max_value[F3_SENSOR], frame.F3);
				//frame.F3 = max(dsp->cf->min_value[F3_SENSOR], frame.F3);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F3)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE; //sin(dsp->counter/5);
				break;
			case F4_SENSOR:
				//frame.F4 = min(dsp->cf->max_value[F4_SENSOR], frame.F4);
				//frame.F4 = max(dsp->cf->min_value[F4_SENSOR], frame.F4);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.F4)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case AF3_SENSOR:
				//frame.AF3 = min(dsp->cf->max_value[AF3_SENSOR], frame.AF3);
				//frame.AF3 = max(dsp->cf->min_value[AF3_SENSOR], frame.AF3);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.AF3)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case AF4_SENSOR:
				//frame.AF4 = min(dsp->cf->max_value[AF4_SENSOR], frame.AF4);
				//frame.AF4 = max(dsp->cf->min_value[AF4_SENSOR], frame.AF4);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.AF4)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			case O2_SENSOR:
				//frame.O2 = min(dsp->cf->max_value[O2_SENSOR], frame.O2);
				//frame.O2 = max(dsp->cf->min_value[O2_SENSOR], frame.O2);
				(dsp->channels[c])[W_SIZE-1][0] = ((double)((frame.O2)-MAX_SENSOR_VALUE))/(double)MAX_SENSOR_VALUE;
				break;
			default:
				printf("shouldn't be here");
		}
        //processing the fft of the channel
        high_pass_filter(dsp,c);
        
        //we only compute the FFT every 32 frame or 4Hz
        //enough redundancy
        if(dsp->counter%32 == 0){
			fft(dsp,c);
			compute_power_band(dsp,c);
			compute_alpha_power(dsp,c);
			compute_beta_power(dsp,c);
		}
    }
    dsp->counter++;
}

void compute_power_band(emokit_dsp* dsp, int channel){
	int j;
	for(j=0; j<W_SIZE; j++){
		dsp->band_power[channel][j][dsp->counter%HISTORY] = log((dsp->f_channels[channel])[j][0]*(dsp->f_channels[channel])[j][0]+(dsp->f_channels[channel])[j][1]*(dsp->f_channels[channel])[j][1]);
	}
}

void compute_alpha_power(emokit_dsp* dsp, int channel){
		dsp->alpha_power[channel][dsp->counter%HISTORY] = compute_power_band_wave(dsp, channel, ALPHA_START, ALPHA_END);
}

void compute_beta_power(emokit_dsp* dsp, int channel){
	dsp->beta_power[channel][dsp->counter%HISTORY] = compute_power_band_wave(dsp, channel, BETA_START, BETA_END);
}

//void compute_average_alpha_power(emokit_dsp* dsp){
	//int i,j;
	////for each channel
	//for(i=0; i<NB_CHANNEL; i++){
		//dsp->average_alpha_power[i] = 0;
		////for each value last HISTORY values
		//for(j=0; j<HISTORY; j++){
			//dsp->average_alpha_power[i] += dsp->alpha_power[i][j]/HISTORY;
		//}
	//}
//}

//void compute_average_beta_power(emokit_dsp* dsp){
	//int i,j;
	////for each channel
	//for(i=0; i<NB_CHANNEL; i++){
		//dsp->average_beta_power[i] = 0;
		////for each value last HISTORY values
		//for(j=0; j<HISTORY; j++){
			//dsp->average_beta_power[i] += dsp->beta_power[i][j]/HISTORY;
		//}
	//}
//}

