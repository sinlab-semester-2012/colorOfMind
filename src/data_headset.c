#include "../lib/emokit/emokit.h"
#include "../lib/emokit/data_headset.h"

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

int createDataFile(data* dat){
    dat->fichier = fopen(dat->name, "w");
    //Test ouverture fichier
    return checkFileOpening(dat->fichier);
}

int openDataFile(data* dat){
	dat->fichier = fopen(dat->name, "r");
	if(checkFileOpening(dat->fichier) ==0){
		rewind(dat->fichier);
		fscanf(dat->fichier, "%d", &dat->nbSamples);
	}
	else return 1;
}

int checkFileOpening(FILE* fichier){
	if (fichier != NULL)
    {
		//TODO changer selon création ou ouverture
        printf("File created ou read sucessfully.\n");
        return 0;
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Error : Couldn't create or open the file in saveEmokitData()\n");
        return 1;
    }
}

int writeData(data* dat, emokit_device* d){
	unsigned int i=0;
	fprintf(dat->fichier, "%d", dat->nbSamples);
	while(i<dat->nbSamples){
		if(emokit_read_data(d) > 0){
			//memset(d->raw_unenc_frame, 0, 32);
			emokit_get_next_raw(d);
		
			int j;
			//we write all bytes of raw unencoded frame in file
			for(j=0; j<32; j++){
				fputc(d->raw_unenc_frame[j],dat->fichier);
			}
			i++;
		}
	}
	printf("Sucess writing the %d samples\n", dat->nbSamples);
	return 0;	
}

int data_get_next_frame(data* dat, emokit_device* d){
	int i = 0;
	//memset(d->raw_unenc_frame, 0, 32);
	//32 +X so the last \n is read with some margin error(reads the entire lign including the \n
	//if we take only 32 the condition stops before the end of the line
	if (dat->readingCursor < dat->nbSamples){
		//index = fgets(&tempTable,32,dat->fichier);
		//fgets(chaine, TAILLE_MAX, fichier);
		for(i=0; i<32; i++){
			d->raw_unenc_frame[i]=fgetc(dat->fichier);
		}
		dat->readingCursor++;
		return 0;
	}
	printf("End of file");	
	return 1;
}

int closeFile(FILE* f){
	fclose(f);
	return 0;
}
