#!/bin/sh

if [ ${PWD##*/} = "colorOfMind" ] ; then echo "Cleaning up";
else echo "Wrong directory. exiting"; exit 1;
fi

#remove temp files
rm -r *~

# clean main directory
rm -r CMakeFiles/
rm CMakeCache.txt cmake_install.cmake install_manifest.txt Makefile

# clean lib directory
cd lib/
rm libemokit.a libemokit_dsp.a liboscpack.so libread_data.a libsave_data.a libplot.a libemotions.a libgnuplot_i.a libofxDmx.a libserial.a
cd ../

# clean examples/emokit_osc directory
cd examples/emotiv/
rm -r CMakeFiles/
rm cmake_install.cmake Makefile
cd ../../

# clean examples/contact directory
cd examples/contact/
rm -r CMakeFiles/
rm cmake_install.cmake Makefile
cd ../../

# clean src directory
cd src/
rm -r CMakeFiles/
rm cmake_install.cmake Makefile
cd ../

# clean include/oscpack directory
cd include/oscpack/
rm -r CMakeFiles/
rm cmake_install.cmake Makefile
cd ../../


# clean bin directory
notDone=true
while($notDone); do
read -p "Do you wish to remove built files from bin/ also? [y/n] " answer
case $answer in
[Yy]* ) notDone=false; rm -r bin/;;
[Nn]* ) notDone=false;;
esac
done

echo "Done"
exit 0
