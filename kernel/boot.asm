section .bss
align 4

global stack_bottom
global stack_top

stack_bottom:
resb 32768
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	extern _init
	call _init

	cli
	extern kernel_main
	call kernel_main

	extern _fini
	call _fini

	cli
.hang:	hlt
	jmp .hang

.end:
