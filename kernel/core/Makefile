ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=cpprts.o core.o

all: $(OBJECTS)

cpprts.o:
	$(CXX) $(CXXFLAGS) -o cpprts.o cpprts.cpp

core.o:
	$(CXX) $(CXXFLAGS) -o core.o core.cpp

clean:
	-rm *.o
