#include "../lib/emokit/emokit.h"
#include <stdlib.h>

//simple mean function
//TODO: remove extreme values
double mean(double* table, int size){
	int i;
	double sum = 0;
	for(i=0; i<size; i++){
		sum += table[i];
	}
	return sum/size;
}

//might be useful for EOG removal
double integrator(double* table, int size){
	int i;
	double sum = 0;
	for(i=1; i<size; i++){
			sum+= table[i]-table[i-1]; 
	}
	return sum/size;
}

//TODO
double variance(double* table){
	return 0;
}
