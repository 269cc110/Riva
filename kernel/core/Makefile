ASM:=nasm
ASMFLAGS=-felf32

CXX:=i686-elf-g++
CXXFLAGS=-c -masm=intel -ffreestanding -fno-exceptions -fno-rtti -O0 -Wall -Wextra -I"../../include" -I"../../librivac/include"

OBJECTS=cpprts.o core.o init.o dt.o gdt.o irq.o isr.o interrupts.o

all: $(OBJECTS)

cpprts.o:
	$(CXX) $(CXXFLAGS) -o cpprts.o cpprts.cpp

core.o:
	$(CXX) $(CXXFLAGS) -o core.o core.cpp

init.o:
	$(ASM) $(ASMFLAGS) -o init.o init.asm

dt.o:
	$(CXX) $(CXXFLAGS) -o dt.o dt.cpp

gdt.o:
	$(ASM) $(ASMFLAGS) -o gdt.o gdt.asm

irq.o:
	$(ASM) $(ASMFLAGS) -o irq.o irq.asm

isr.o:
	$(ASM) $(ASMFLAGS) -o isr.o isr.asm

interrupts.o:
	$(CXX) $(CXXFLAGS) -o interrupts.o interrupts.cpp

clean:
	-rm *.o

