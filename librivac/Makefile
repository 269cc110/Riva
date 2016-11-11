ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"include" -I"../include"

AR:=i686-elf-ar
ARFLAGS=-r librivac.a

OBJECTS=string.o

all: archive

string.o:
	$(CXX) $(CXXFLAGS) -o string.o string.c

archive: $(OBJECTS)
	$(AR) $(ARFLAGS) $(OBJECTS)

clean:
	-rm *.o *.a
