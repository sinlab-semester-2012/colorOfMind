
/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>

#include "emokit/emokit.h"
#include "emokit/save_data.h"
  
void adjustHeadset(struct emokit_device* d){
	int i;
	int nbUnsetCaptor=0;
	int quit =0;
	char answer;
	struct emokit_frame c;
	do{
		for(i=0; i<256; i++){
			if(emokit_read_data(d) > 0)
			{
				c = emokit_get_next_frame(d);
			}
		}
		nbUnsetCaptor=0;
		if(c.cq.F3<4000){
			printf("Captor F3 is not set up correctly, value : %i\n", c.cq.F3);
			nbUnsetCaptor++;
		}
		if(c.cq.F4<4000){
			printf("Captor F4 is not set up correctly, value : %i\n", c.cq.F4);
			nbUnsetCaptor++;
		}
		if(c.cq.AF3<4000){
			printf("Captor AF3 is not set up correctly, value : %i\n", c.cq.AF3);
			nbUnsetCaptor++;
		}
		if(c.cq.AF4<4000){
			printf("Captor AF4 is not set up correctly, value : %i\n", c.cq.AF4);
			nbUnsetCaptor++;
		}
		if(c.cq.O2<4000){
			printf("Captor O2 is not set up correctly, value : %i\n", c.cq.O2);
			nbUnsetCaptor++;
		}
		if(nbUnsetCaptor == 0){
			printf("All captors are set up correctly. Launching the program\n");
			quit = 1;
		}
		else{
			printf("Please Adjust headset. Continue anyway ? y/n\n");
			scanf(" %c", &answer);
			if(answer == 'y' || answer == 'Y'){
				quit =1;
			}
		}
	}while(!quit);
}   

void ready_start(){
	char answer = 'n';
	printf("Are you ready to start the experiment ? \n");
	while(answer != 'y'){
		scanf(" %c", &answer);
	}
}

int main(int argc, char **argv)
{
	struct emokit_device* d;
	d = emokit_create();
	
	char* name = argv[1];
	
	//*** Check epoc connected
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 1);
	if(r != 0)
	{
		printf("CANNOT CONNECT: %d\n", r);
		return 1;
	}
	printf("Connected\n");
	
	adjustHeadset(d);
	int k=0;
	ready_start();
	
	//** 1st step Normal : 10 sec = 1280 samples**
	data* dat;
	dat = new_data(strcat(argv[1],"_start"), 10);
	if(create_data_file(dat)>0){
			printf("Error creating the file\nClosing the program\n");
			return 1;
	};
	write_data(dat, d);
	close_data(dat);

	
	//** 1bis step Neutral : 15 sec = 1280 samples**
	data* dat1;
	dat1 = new_data(strcat(argv[1],"_neutral1"), 15);
	if(create_data_file(dat1)>0){
			printf("Error creating the file\nClosing the program\n");
			return 1;
	};
	write_data(dat1, d);
	close_data(dat1);
	
	//2nd step HAPPY memory: 15 sec
	printf("Think about a happy memory\n");
	sleep(3);
	data* dat2;
	dat2 = new_data(strcat(argv[1],"_happy"), 15);
	if(create_data_file(dat2)>0){
			printf("Error creating the file\nClosing the program\n");
			return 1;
	};
	write_data(dat2, d);
	close_data(dat2);
	
	//3rd step NEUTRAL: 15 sec
	printf("Try to relax and clear your mind\n");
	sleep(3);
	data* dat3;
	dat3 = new_data(strcat(argv[1],"_neutral2"), 15);
	if(create_data_file(dat3)>0){
			printf("Error creating the file\nClosing the program\n");
			return 1;
	};
	write_data(dat3, d);
	close_data(dat3);
	
	//3rd step SAD memory
	printf("Think about a sad memory\n");
	sleep(3);
	data* dat4;
	dat4 = new_data(strcat(argv[1],"_sad"), 15);
	if(create_data_file(dat4)>0){
			printf("Error creating the file\nClosing the program\n");
			return 1;
	};
	write_data(dat4, d);
	close_data(dat4);
	
	printf("Thank you, it's over\n");

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
