##colorOfMind - A brain computer guided environment


The purpose of this program is to map the state of mind of the user using the Emotiv EPOC headset with a RGB spot light.
The project is using the Emokit driver to get raw packets from the device and FFTW to process the signal.

For more infos:
*The project, please check the wiki : https://github.com/sinlab-semester-2012/colorOfMind/wiki
*Emotiv EPOC : http://en.wikipedia.org/wiki/Emotiv_Systems#Emotiv_EPOC
*SINLAB : http://www.sinlab.ch/


##Required Libraries
==================

###Emokit  
*CMake - http://www.cmake.org  
*libmcrypt - https://sourceforge.net/projects/mcrypt/  
*hidapi - http://www.signal11.us/oss/hidapi/  

###Signal Processing
*FFTW 3.3 - http://www.fftw.org/download.html  

###Dmx (optional)
*oscpack - Modified version already included in colorOfMind  
*Processing - http://processing.org/  
*DMXP512 - http://motscousus.com/stuff/2011-01_dmxP512/  

###Plot (optional)
*Gnuplot - http://www.gnuplot.info/faq/faq.html


##Install

On linux :
Install the dependencies  
Use the build.sh script  
"./bin/emotiv" to get the datas from the headset or a file  
"./bin/contact" to get the real-time value of the sensors  
"./bin/lightShow" to start the light show  

On windows :
Should work not tested yet

##Platform Specifics Issues
=========================

####Linux
-----

"Due to the way hidapi works, the linux version of emokit can run using
either hidraw calls or libusb. These will require different udev rules
for each. We've tried to cover both (as based on hidapi's example udev
file), but your mileage may vary. If you have problems, please post
them to the github issues page (http://github.com/openyou/emokit/issues)."
