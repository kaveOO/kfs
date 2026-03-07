BITS 32

section .multiboot
	ALIGN 4
	dd 0x1BADB002
	dd 0x00000000
	dd -(0x1BADB002 + 0x00000000)

section .text

global start
extern kmain
global stack_bottom
global stack_top

section .gdt

gdt_start:

gdt_null:
	dq 0

gdt_kernel_code:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00

gdt_kernel_data:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_kernel_stack:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_user_code:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 11111010b
	db 11001111b
	db 0x00

gdt_user_data:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 11110010b
	db 11001111b
	db 0x00

gdt_user_stack:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 11110010b
	db 11001111b
	db 0x00

gdt_end:

section .text

gdtr:
	dw gdt_end - gdt_start - 1
	dd gdt_start

start:
	cli
	mov esp, stack_top
	lgdt [gdtr]
	jmp 0x08:reload_cs

reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, 0x18
	mov ss, ax
	call kmain
	hlt

halt_kernel:
	cli
	hlt
	jmp halt_kernel

section .bss
stack_bottom:
	resb 4096
stack_top:
