#include "emokit/read_data.h"

data* new_data(char* name, unsigned int nbSamples){	
    data* dat = (data*)malloc(sizeof(data));
    //12 letters max
    //TODO : check input or bufferoverflow possible
    dat->name = (char*)malloc(sizeof(char)*50);
    strncpy(dat->name, name, 50);
    dat->nbSamples = nbSamples;
    dat->fichier = NULL;
    dat->readingCursor = 0;
    return dat;
}

int open_data_file(data* dat){
	dat->fichier = fopen(dat->name, "r");
	if(check_file_opening(dat->fichier) ==0){
		rewind(dat->fichier);
		fscanf(dat->fichier, "%d", &dat->nbSamples);
		return 0;
	}
	else return 1;
}

int check_file_opening(FILE* fichier){
	if (fichier != NULL)
    {
		//TODO changer selon création ou ouverture
        printf("File read sucessfully.\n");
        return 0;
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Error : Couldn't open the file in saveEmokitData()\n");
        return 1;
    }
}

struct emokit_frame data_get_next_frame(data* dat){
	//recompose an emokit_frame
	struct emokit_frame k;
	memset(&k.cq,0,sizeof(struct emokit_contact_quality));
	
	//battery, counter and contact quality are not store
	k.counter = 0;
	k.battery = 0;
	int gyroX, gyroY;
	fscanf(dat->fichier, "data: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n", &k.F3,&k.FC6,&k.P7,&k.T8,&k.F7,&k.F8,&k.T7,&k.P8,&k.AF4,&k.F4,&k.AF3,&k.O2,&k.O1,&k.FC5,&gyroX,&gyroY); 
	k.gyroX = (char) gyroX;
	k.gyroY = (char) gyroY;
	//printf("%c", gyroX);
	return k;
}

int close_data(data* d){
	free(d->name);
	fclose(d->fichier);
	free(d);
	return 0;
}
