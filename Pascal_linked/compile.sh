#!/bin/bash
date
rm -f fft.o
rm -f libfft.a
rm -f kernel7.img
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c test_complex.c
arm-none-eabi-ar rcs libfft.a test_complex.o

fpc -vi -B -Tultibo -Parm -CpARMV7A -WpRPI2B @/home/pi/ultibo/core/fpc/bin/rpi2.cfg -O2 LibC_FFT_RPi2.lpr
ls -la test_complex.o libfft.a kernel7.img
