ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=util.o

all: $(OBJECTS)

util.o:
	$(CXX) $(CXXFLAGS) -o util.o util.cpp

clean:
	-rm *.o
