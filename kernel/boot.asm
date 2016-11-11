MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4

	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 4

stack_bottom:
resb 32768
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	extern _init
	call _init

	extern kernel_main
	call kernel_main

	extern _fini
	call _fini

	cli
.hang:	hlt
	jmp .hang

.end:
