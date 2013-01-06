#include "emokit/save_data.h"

data* new_data(char* name, unsigned int t){	
    data* dat = (data*)malloc(sizeof(data));

    dat->name = (char*)malloc(sizeof(char)*50);
    strncpy(dat->name, name, 50);
    //128 packets per second
    dat->nbSamples = t*128;
    dat->fichier = NULL;

    dat->readingCursor = 0;
    dat->play = 1;
    return dat;
    
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
		if(i%(5*128)==0){
				printf("%d sec\n", i/128);
		}
	}
	printf("Sucess writing the %u samples\n", dat->nbSamples);
	return 0;	
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
	
	//battery, counter and contact quality are not stored
	k.counter = 0;
	k.battery = 0;
	int gyroX, gyroY;
	dat->play = fscanf(dat->fichier, "data: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n", &k.F3,&k.FC6,&k.P7,&k.T8,&k.F7,&k.F8,&k.T7,&k.P8,&k.AF4,&k.F4,&k.AF3,&k.O2,&k.O1,&k.FC5,&gyroX,&gyroY); 
	if(dat->play == 0){
			exit(EXIT_FAILURE);
	}
	k.gyroX = (char) gyroX;
	k.gyroY = (char) gyroY;
	return k;
}

int close_data(data* d){
	free(d->name);
	fclose(d->fichier);
	free(d);
	return 0;
}
