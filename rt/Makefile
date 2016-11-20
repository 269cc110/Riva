ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I ../include -I ../librivac/include

OBJECTS=crti.o crtn.o cpp.o

all: $(OBJECTS)

crti.o:
	$(ASM) $(ASMFLAGS) -o crti.o crti.asm

crtn.o:
	$(ASM) $(ASMFLAGS) -o crtn.o crtn.asm

cpp.o:
	$(CXX) $(CXXFLAGS) -o cpp.o cpp.cpp

clean:
	-rm *.o
