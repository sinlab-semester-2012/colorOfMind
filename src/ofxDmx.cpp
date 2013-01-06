#include "../include/dmx512/ofxDmx.h"

#define DMX_PRO_HEADER_SIZE 4
#define DMX_PRO_START_MSG 0x7E
#define DMX_START_CODE 0
#define DMX_START_CODE_SIZE 1
#define DMX_PRO_SEND_PACKET 6 // "periodically send a DMX packet" mode
#define DMX_PRO_END_SIZE 1
#define DMX_PRO_END_MSG 0xE7

ofxDmx::ofxDmx()
:connected(false)
,needsUpdate(false) {
}

ofxDmx::~ofxDmx() {
	connected = false;
}

bool ofxDmx::connect(const char* port, unsigned int channels) {
	fd = serialport_init(port, B115200);
	connected = false;
	if(fd != -1){
		connected = true;
	}
	setChannels(channels);
	return connected;
}

bool ofxDmx::isConnected() {
	return connected;
}

void ofxDmx::disconnect() {
}

void ofxDmx::setChannels(unsigned int channels) {
	if(channels<1){
		channels = 1;
	} else if(channels >512){
		channels = 512;
	}
	size = channels;
	levels = (unsigned char*)malloc((size)*sizeof(int));
}

void ofxDmx::update() {
	if(needsUpdate) {
		std::cout << "Update\n";
		needsUpdate = false;
		unsigned int dataSize = size + DMX_START_CODE_SIZE;
		unsigned int packetSize = DMX_PRO_HEADER_SIZE + dataSize + DMX_PRO_END_SIZE;
		unsigned char* packet = (unsigned char*)malloc((size+6)*sizeof(int));
		
		// header
		packet[0] = DMX_PRO_START_MSG;
		packet[1] = DMX_PRO_SEND_PACKET;
		packet[2] = dataSize & 0xff; // data length lsb
		packet[3] = (dataSize >> 8) & 0xff; // data length msb
		
		// data
		packet[4] = DMX_START_CODE; // first data byte
		memcpy(&packet[5], &levels[0], size);
		// end
		packet[packetSize - 1] = DMX_PRO_END_MSG;
		//int n= serialport_write(fd, &packet[0]);
		
		serialport_writebyte( fd, DMX_PRO_START_MSG);
		serialport_writebyte( fd, DMX_PRO_SEND_PACKET);
		serialport_writebyte( fd, dataSize & 0xff);
		serialport_writebyte( fd, (dataSize >> 8) & 0xff);
		serialport_writebyte( fd, DMX_START_CODE);
		int i=0;
		for(i=0; i<size; i++){
			serialport_writebyte( fd, packet[i+5]);
		}
		serialport_writebyte( fd, DMX_PRO_END_MSG);
		usleep(1200);
//#ifdef OFXDMX_SPEW
		//std::cout << "@" << ofGetSystemTime() << endl;
		//for(int i = 0; i < packetSize; i++) {
			//std::cout << setw(2) << hex << (int) packet[i];
			//if((i + 1) % 8 == 0) {
				//st::cout << endl;
			//}
		//}
//#endif
	}
}

bool ofxDmx::badChannel(unsigned int channel) {
	if(channel > size) {
		std::cout << "Channel " << channel << " is out of bounds. Only " << size << " channels are available.\n";
		return true;
	}
	if(channel == 0) {
		std::cout << "Channel 0 does not exist. DMX channels start at 1.\n";
		return true;
	}
	return false;
}

void ofxDmx::setLevel(unsigned int channel, unsigned char level) {
	if(badChannel(channel)) {
		return;
	}
	channel--; // convert from 1-initial to 0-initial
	if(level != levels[channel]) {
		levels[channel] = (unsigned char) level;
		needsUpdate = true;
	}
}

void ofxDmx::clear() {
	for (int i = 0; i < size; i++) {
		levels[i] = 0;
	}
}

unsigned char ofxDmx::getLevel(unsigned int channel) {
	if(badChannel(channel)) {
		return 0;
	}
	channel--; // convert from 1-initial to 0-initial
	return levels[channel];
}
