%macro ISR_NEC 1
global _isr%1
_isr%1:
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro ISR_EC 1
global _isr%1
_isr%1:
	push byte 0
	jmp isr_common_stub
%endmacro

ISR_NEC 0
ISR_NEC 1
ISR_NEC 2
ISR_NEC 3
ISR_NEC 4
ISR_NEC 5
ISR_NEC 6
ISR_NEC 7
ISR_EC 8
ISR_NEC 9
ISR_EC 10
ISR_EC 11
ISR_EC 12
ISR_EC 13
ISR_EC 14
ISR_NEC 15
ISR_NEC 16
ISR_NEC 17
ISR_NEC 18
ISR_NEC 19
ISR_NEC 20
ISR_NEC 21
ISR_NEC 22
ISR_NEC 23
ISR_NEC 24
ISR_NEC 25
ISR_NEC 26
ISR_NEC 27
ISR_NEC 28
ISR_NEC 29
ISR_NEC 30
ISR_NEC 31

extern _fault_handler

isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, _fault_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret


