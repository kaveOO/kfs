#include "stack.h"

void print_stack(enum StackType stack) {
	switch (stack)
	{
		case GDT:
			hexdump(
				(unsigned char *)&gdt_start,
				(unsigned char *)&gdt_end
			);
			break;
		case IDT:
			hexdump(
				(unsigned char *)&idt_start,
				(unsigned char *)&idt_end
			);
			break;
		case KERNEL:
			hexdump(
				(unsigned char *)&stack_bottom,
				(unsigned char *)&stack_top
			);
			break;
		case KERNEL_EXEC:
			hexdump(
				(unsigned char *)get_esp(),
				(unsigned char *)&stack_top
			);
			break;
		default:
			break;
	}
}

void hexdump(unsigned char *start, unsigned char *end) {
	char hex_digits[] = "0123456789abcdef";

	while (start < end) {
		printk(WHITE, "0x%x  ", start); // TODO handle %p here

		for (int i = 0; i < DUMP_SIZE; i++) {
			unsigned char byte = start[i];

			writek(hex_digits[byte >> 4], 1, WHITE);
			writek(hex_digits[byte & 0xF], 1, WHITE);
			writek(' ', 1, WHITE);

			if (DUMP_SIZE == 16 && i == 7)
				writek(' ', 1, WHITE);
		}

		writek(' ', 1, WHITE);

		for (int i = 0; i < DUMP_SIZE; i++) {
			unsigned char c = start[i];

			if (c >= 32 && c <= 126)
				writek(c, 1, WHITE);
			else
				writek('.', 1, WHITE);
		}

		writek('\n', 1, WHITE);

		start += DUMP_SIZE;
	}
}
