ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"include" -I"../include"

AR:=i686-elf-ar
ARFLAGS=-r librivac.a

OBJECTS=string.o alloc.o strconv.o strutil.o

all: archive

string.o:
	$(CXX) $(CXXFLAGS) -o string.o string.cpp

alloc.o:
	$(CXX) $(CXXFLAGS) -o alloc.o alloc.cpp

strconv.o:
	$(CXX) $(CXXFLAGS) -o strconv.o strconv.cpp

strutil.o:
	$(CXX) $(CXXFLAGS) -o strutil.o strutil.cpp

archive: $(OBJECTS)
	$(AR) $(ARFLAGS) $(OBJECTS)

clean:
	-rm *.o *.a

