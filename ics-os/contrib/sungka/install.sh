make &&
make clean &&
make install &&
cd ../.. &&
make &&
make clean &&
sudo make install &&
qemu-system-i386 -fda ics-os-floppy.img
#200x320
