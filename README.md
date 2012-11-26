
ColorOfMind 
===========

The purpose of this program is to map the state of mind of the user using the Emotiv EPOC headset with a RGB spot light. The project is using the Emokit driver to get raw packets from the device.
=======
colorOfMind :
A brain computer guided environment
__________________________________________________________________________________

The purpose of this program is to map the state of mind of the user using the Emotiv EPOC headset with a RGB spot light.
The project is using the Emokit driver to get raw packets from the device.





Set up :

Install the following libraries on your computer:
Mcrypt
libusb
FFTW
oscpack


Install

On linux :
Use the build.sh script


Required Libraries
==================

* Emokit - https://github.com/openyou/emokit/
* CMake - http://www.cmake.org
* libmcrypt - https://sourceforge.net/projects/mcrypt/
* hidapi - http://www.signal11.us/oss/hidapi/
* FFTW - http://www.fftw.org/
* oscpack - http://code.google.com/p/oscpack/

Platform Specifics Issues
=========================

Linux
-----

Due to the way hidapi works, the linux version of emokit can run using
either hidraw calls or libusb. These will require different udev rules
for each. We've tried to cover both (as based on hidapi's example udev
file), but your mileage may vary. If you have problems, please post
them to the github issues page (http://github.com/openyou/emokit/issues).
