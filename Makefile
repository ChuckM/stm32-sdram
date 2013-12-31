# I've used the libopencm3 Makefiles as a template here.

OBJS = clock.o uart.o debug.o sdram.o dump.o term.o
BINARY = main

LDSCRIPT = stm32f429.ld

include ../../Makefile.include

