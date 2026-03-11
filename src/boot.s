BITS 32

extern kmain
extern keyboard_handler

global start
global stack_bottom
global stack_top
global keyboard_isr

global gdt_start
global gdt_end

global idt_start
global idt_end

section .multiboot
	ALIGN 4
	dd 0x1BADB002
	dd 0x00000000
	dd -(0x1BADB002 + 0x00000000)

section .bss
	stack_bottom:
		resb 4096
	stack_top:

	idt:
		resb (256 * 8)

section .gdt

gdt_start:

gdt_null:
	dq 0

; 0x08
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

gdtr:
	dw gdt_end - gdt_start - 1
	dd gdt_start

section .idt

idtr:
	dw ((256 * 8) - 1)
	dd idt

pic_remap:
	mov al, 0x11
	out 0x20, al
	out 0xA0, al

	mov al, 0x20
	out 0x21, al

	mov al, 0x28
	out 0xA1, al

	mov al, 0x04
	out 0x21, al

	mov al, 0x02
	out 0xA1, al

	mov al, 0x01
	out 0x21, al
	out 0xA1, al

	mov al, 0xFD
	out 0x21, al
	mov al, 0xFF
	out 0xA1, al

idt_start:

set_idt_entry:
	; eax = interrupt number
	; ebx = handler address
	push edx

	lea edx, [idt + eax * 8]

	mov word [edx], bx
	mov word [edx + 2], 0x08
	mov byte [edx + 4], 0
	mov byte [edx + 5], 10001110b

	shr ebx, 16
	mov word [edx + 6], bx

	pop edx
	ret

keyboard_isr:
	pushad
	call keyboard_handler
	popad

	mov al, 0x20
	out 0x20, al
	iret

idt_end:

section .text

start:
	cli

	mov esp, stack_top

	lgdt [gdtr]
	lidt [idtr]

	jmp 0x08:reload_cs

reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	call pic_remap

	mov eax, 0x21
	mov ebx, keyboard_isr
	call set_idt_entry

	sti
	call kmain

.halt:
	hlt
	jmp .halt
