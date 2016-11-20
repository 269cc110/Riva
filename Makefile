ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"include/" -I"librivac/include"

LD:=i686-elf-g++
LDFLAGS=-T linker.ld -o rivak.bin -ffreestanding -O0 -nostdlib -L librivac/ -l rivac -l gcc

CRTBEGIN:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTI:=rt/crti.o
CRTN:=rt/crtn.o

OBJECTS_CORE=kernel/core/init.o kernel/core/core.o kernel/core/cpprts.o
OBJECTS_DRV=kernel/drv/vga.o
OBJECTS_API=kernel/api/ports.o
OBJECTS_LRC=librivac/string.o librivac/alloc.o librivac/strconv.o librivac/strutil.o
OBJECTS_ALL=kernel/boot.o $(OBJECTS) $(OBJECTS_CORE) $(OBJECTS_LRC) $(OBJECTS_DRV) $(OBJECTS_API)

all: iso

sub:
	cd librivac/ && $(MAKE)
	cd kernel/ && $(MAKE)
	cd rt/ && $(MAKE)

kernel: sub
	$(LD) $(LDFLAGS) $(CRTI) $(CRTBEGIN) $(OBJECTS_ALL) $(CRTEND) $(CRTN)

iso: kernel
	grub-file --is-x86-multiboot rivak.bin
	mkdir -p iso/boot/grub/
	cp grub.cfg iso/boot/grub/
	cp rivak.bin iso/boot/
	grub-mkrescue -o riva.iso iso/

clean:
	-rm -r *.bin *.iso iso/
	cd kernel/ && $(MAKE) clean
	cd rt/ && $(MAKE) clean
	cd librivac/ && $(MAKE) clean
