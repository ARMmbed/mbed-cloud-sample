#!/bin/sh

# toolchain specific settings
PWD="`pwd`"
EXE="`basename ${PWD}`"

#
# Machine dependent
MACHINE=NUCLEO_F411RE
BOOTLOADER=mbed-bootloader-nucleo_f411re-block_device-sotp-v3_3_0_2f113f3.bin

#
# Exec (format dependent)
EXEC="BUILD/${MACHINE}/GCC_ARM/${EXE}.bin"

#
# Output file format dependent
OUTFILE=combined.bin

set -x

# Build for mbedOS on the MACHINE using the GCC toolchain
mbed compile -m ${MACHINE} -t GCC_ARM -c -j0 $*

# add the bootloader (REQUIRED)
echo "Finalizing image: " ${EXEC}
tools/combine_bootloader_with_app.py -b tools/${BOOTLOADER} -m ${MACHINE} -a ${EXEC} -o ${OUTFILE}
