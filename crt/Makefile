ASM:=nasm
ASMFLAGS=-felf32

OBJECTS=crti.o crtn.o

all: $(OBJECTS)

crti.o:
	$(ASM) $(ASMFLAGS) -o crti.o crti.asm

crtn.o:
	$(ASM) $(ASMFLAGS) -o crtn.o crtn.asm

clean:
	-rm *.o
