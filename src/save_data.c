#include "emokit/save_data.h"

data* new_data(char* name, unsigned int t){	
    data* dat = (data*)malloc(sizeof(data));

    //TODO : check input or bufferoverflow possible
    dat->name = (char*)malloc(sizeof(char)*50);
    strncpy(dat->name, name, 50);
    //128 packets per second
    dat->nbSamples = t*128;
    dat->fichier = NULL;
    return dat;
}

int create_data_file(data* dat){
    dat->fichier = fopen(dat->name, "w");
    //Test ouverture fichier
    return check_file_creation(dat->fichier);
}

int check_file_creation(FILE* fichier){
	if (fichier != NULL)
    {
		//TODO changer selon création ou ouverture
        printf("File created sucessfully.\n");
        return 0;
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Error : Couldn't create the file in saveEmokitData()\n");
        return 1;
    }
}

int write_data(data* dat, struct emokit_device* d){
	unsigned int i=0;
	printf("writing ... Please Wait\n");
	while(i < dat->nbSamples){
		if(emokit_read_data(d)>0){
			struct emokit_frame f;
			f=emokit_get_next_frame(d);
			//emokit frame :
			//int F3, FC6, P7, T8, F7, F8, T7, P8, AF4, F4, AF3, O2, O1, FC5; //raw data values
			//char gyroX, gyroY;
			fprintf(dat->fichier, "data: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n", f.F3,f.FC6,f.P7,f.T8,f.F7,f.F8,f.T7,f.P8,f.AF4,f.F4,f.AF3,f.O2,f.O1,f.FC5,f.gyroX,f.gyroY);
			i++;
		}
	}
	printf("Sucess writing the %u samples\n", dat->nbSamples);
	return 0;	
}

int close_data(data* d){
	free(d->name);
	fclose(d->fichier);
	free(d);
	return 0;
}
