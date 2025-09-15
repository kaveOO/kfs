BITS 32

section .text
	ALIGN 4							; Next -> multiple of 4 bytes
	dd 0x1BADB002 					; Grub magic number https://wiki.osdev.org/Multiboot
	dd 0x00000000
	dd -(0x1BADB002 + 0x00000000) 	; Checksum

global start
extern kmain						; Kernel Main

start:
	cli
	mov esp, stack_space
	call kmain
	hlt

HalthKernel:
	cli
	hlt
	jmp HalthKernel

section .bss
resb 8192
stack_space:
