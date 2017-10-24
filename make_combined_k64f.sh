#!/bin/sh

PWD="`pwd`"
EXE="`basename ${PWD}`"
EXEC="BUILD/K64F/GCC_ARM/${EXE}.bin"

echo "Finalizing image: " ${EXEC}

echo tools/combine_bootloader_with_app.py -b tools/mbed-bootloader-k64f.bin -a ${EXEC} --app-offset 0x20400 --header-offset 0x20000 -o ${EXE}-combined.bin 
tools/combine_bootloader_with_app.py -b tools/mbed-bootloader-k64f.bin -a ${EXEC} --app-offset 0x20400 --header-offset 0x20000 -o ${EXE}-combined.bin 
