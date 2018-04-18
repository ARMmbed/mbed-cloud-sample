#!/bin/sh

# K64F/GCC toolchain specific settings
PWD="`pwd`"
EXE="`basename ${PWD}`"
EXEC="BUILD/K64F/GCC_ARM/${EXE}.bin"
BOOTLOADER=mbed-bootloader-k64f-block_device-sotp-v3_3_0.bin

#
# combined.bin - will overwrite creds and force a re-register of the device
# combined.hex - will NOT overwrite creds
#
# OUTFILE=combined.hex
OUTFILE=combined.bin

set -x

# Build for mbedOS on the K64F using the GCC toolchain
mbed compile -m K64F -t GCC_ARM -c -j0 $*

# add the bootloader (REQUIRED)
echo "Finalizing image: " ${EXEC}
tools/combine_bootloader_with_app.py -b tools/${BOOTLOADER} -m K64F -a ${EXEC} -o ${OUTFILE}
