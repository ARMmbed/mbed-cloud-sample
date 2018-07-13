#!/bin/sh

# toolchain specific settings
PWD="`pwd`"
EXE="`basename ${PWD}`"

#
# Machine dependent
MACHINE=K64F
BOOTLOADER=mbed-bootloader-k64f-block_device-sotp-v3_3_0.bin

#
# Executable
EXEC="BUILD/K64F/GCC_ARM/${EXE}.bin"

#
# Output file format dependent
OUTFILE=combined.bin

set -x

# Build for mbedOS on the MACHINE using the GCC toolchain
mbed compile -m ${MACHINE} -t GCC_ARM -c -j0 $*

# add the bootloader (REQUIRED)
echo "Finalizing image: " ${EXEC}
tools/combine_bootloader_with_app.py -b tools/${BOOTLOADER} -m ${MACHINE} -a ${EXEC} -o ${OUTFILE}
