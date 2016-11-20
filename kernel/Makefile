ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../librivac/include" -I"../include"

OBJECTS=boot.o

all: $(OBJECTS) sub

boot.o:
	$(ASM) $(ASMFLAGS) -o boot.o boot.asm

sub:
	cd drv/ && $(MAKE)
	cd api/ && $(MAKE)
	cd core/ && $(MAKE)
#	cd util/ && $(MAKE)

clean:
	-rm *.o
	cd drv/ && $(MAKE) clean
	cd api/ && $(MAKE) clean
	cd core/ && $(MAKE) clean
#	cd util/ && $(MAKE) clean
