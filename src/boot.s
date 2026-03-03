BITS 32

section .multiboot
	ALIGN 4			; Next -> multiple of 4 bytes
	dd 0x1BADB002	; Grub magic number https://wiki.osdev.org/Multiboot
	dd 0x00000000
	dd -(0x1BADB002 + 0x00000000)	; Checksum

section .text

global start
extern kmain	; Kernel Main

null:				; 0x00
	dq	0

kernel_code:		; 0x10
	dw	0xFFFF		; limit low
	dw	0x0000		; base low
	db	0x00		; base middle
	db	10011010b	; access
	db	11001111b	; granularity
	db	0x00		; base high

kernel_data:
	dw	0xFFFF
	dw	0x0000
	db	0x00
	db	10010010b
	db	11001111b
	db	0x00

; kernel_stack:
; 	dw	0xFFFF
; 	dw	0x0000
; 	db	0x00
; 	db
; 	db
; 	db	0x00

user_code:
	dw	0xFFFF
	dw	0x0000
	db	0x00
	db	11111010b
	db	11001111b
	db	0x00

user_data:
	dw	0xFFFF
	dw	0x0000
	db	0x00
	db	11110010b
	db	11001111b
	db	0x00

; user_stack:
; 	dw	0xFFFF
; 	dw	0x0000
; 	db	0x00
; 	db
; 	db
; 	db	0x00

end_of_gdt:
toc:
	dw end_of_gdt - null - 1	; Size of the GDT
	dd null					; Base of GDT

start:
	cli
	mov esp, stack_space
	lgdt [toc]
	jmp	0x08:reload_cs

reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	call kmain
	hlt

halt_kernel:
	cli
	hlt
	jmp halt_kernel

section .bss
resb 8192
stack_space:
