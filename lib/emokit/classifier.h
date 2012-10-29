#include "../lib/emokit/emokit.h"


//simple mean function
//TODO: remove extreme values
double mean(double* table){
	int i;
	double sum = 0;
	for(i=0; i<table.length(); i++){
		sum += table[i];
	}
	return sum/table.length();
}

//TODO
double variance(double* table){
	return 0;
}
