//#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>

extern "C"{
#include "serial.h"
} 

class ofxDmx {
public:
	ofxDmx();
	~ofxDmx();
	
	// connect to the serial port. valid number of channels is 24-512. performance
	// is directly related to the number of channels, so use the minimum required.
	bool connect(const char* port, unsigned int channels);
	void disconnect();
	
	void setLevel(unsigned int channel, unsigned char level);
	void clear();
	unsigned char getLevel(unsigned int channel);	
	void update(); // send a packet to the dmx controller
	
	void setChannels(unsigned int channels); // change the number of channels
	bool isConnected();
	
private:	
	int connected;
	int fd;
	int size;
	unsigned char* levels;
	bool needsUpdate;
	
	bool badChannel(unsigned int channel);
};
