ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=ports.o

all: $(OBJECTS)

ports.o:
	$(CXX) $(CXXFLAGS) -o ports.o ports.cpp

clean:
	-rm *.o
