ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../include" -I"../include"

LD:=i686-elf-g++
LDFLAGS=-T linker.ld -o rivak.bin -ffreestanding -O0 -nostdlib -lgcc

CRTBEGIN:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTI:=crt/crti.o
CRTN:=crt/crtn.o

OBJECTS=boot.o

all: $(OBJECTS) sub

boot.o:
	$(ASM) $(ASMFLAGS) -o boot.o boot.asm

sub:
	cd drv/ && $(MAKE)
	cd api/ && $(MAKE)
	cd core/ && $(MAKE)

clean:
	-rm *.o
	cd drv/ && $(MAKE) clean
	cd api/ && $(MAKE) clean
	cd core/ && $(MAKE) clean
