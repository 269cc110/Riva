ASM:=nasm
ASMFLAGS=-felf32

CC:=i686-elf-gcc
CCFLAGS=-c -ffreestanding -O0 -Wall -Wextra -I"include" -I"../include"

AR:=i686-elf-ar
ARFLAGS=-r librivac.a

OBJECTS=string.o

all: archive

string.o:
	$(CC) $(CCFLAGS) -o string.o string.c

archive: $(OBJECTS)
	$(AR) $(ARFLAGS) $(OBJECTS)

clean:
	-rm *.o *.a
