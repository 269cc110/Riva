section .text
global _init_page_dir:function
_init_page_dir:
	push ebp
	mov ebp, esp
	mov eax, [esp + 8]
	mov cr3, eax
	mov esp, ebp
	pop ebp
	ret

global _enable_paging:function
_enable_paging:
	push ebp
	mov ebp, esp
	push eax
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	pop eax
	mov esp, ebp
	pop ebp
	ret

