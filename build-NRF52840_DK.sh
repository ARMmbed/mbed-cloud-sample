#!/bin/sh

# toolchain specific settings
PWD="`pwd`"
EXE="`basename ${PWD}`"

#
# Machine dependent
MACHINE=NRF52840_DK
BOOTLOADER=mbed-bootloader-NRF52840_DK.hex

#
# Executable
EXEC="BUILD/${MACHINE}/GCC_ARM/${EXE}.hex"

#
# Output file format dependent
OUTFILE=combined.hex

set -x

# Build for mbedOS on the MACHINE using the GCC toolchain
mbed compile -m ${MACHINE} -t GCC_ARM -c -j0 $*

# add the bootloader (REQUIRED)
echo "Finalizing image: " ${EXEC}
tools/combine_bootloader_with_app.py -b tools/${BOOTLOADER} -m ${MACHINE} -a ${EXEC} -o ${OUTFILE}
