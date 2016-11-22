ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=vga.o

all: $(OBJECTS)

vga.o:
	$(CXX) $(CXXFLAGS) -o vga.o vga.cpp

clean:
	-rm *.o

