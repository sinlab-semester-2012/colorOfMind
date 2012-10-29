#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../lib/emokit/emokit.h"
#include "../../lib/emokit/data_headset.h"

int main(int argc, char **argv)
{
	//Initialize the structure for decoding device data
	emokit_device* d;
	d = emokit_create();
	data* dat;
	int nbSamples = atoi(argv[2]);
	dat = new_data(argv[1], nbSamples);
	//should return value to know if everything ok
	createDataFile(dat);
	
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}
	
	writeData(dat, d);
	closeFile(dat->fichier);
	fflush(stdout);

	emokit_close(d);
	emokit_delete(d);
	return 0;
}

