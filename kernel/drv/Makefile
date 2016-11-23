ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=vga.o kb.o

all: $(OBJECTS)

vga.o:
	$(CXX) $(CXXFLAGS) -o vga.o vga.cpp

kb.o:
	$(CXX) $(CXXFLAGS) -o kb.o kb.cpp

clean:
	-rm *.o

