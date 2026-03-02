#include "gdt.h"

extern void gdt_flush(uint32_t ptr);

t_gdt_entry	gdt_entries[ENTRIES];
t_gdt_ptr	gdt_ptr;

static void set_gdt_gate(
	uint32_t	base,
	uint32_t	limit,
	uint8_t		access,
	uint8_t		granularity
)
{
	static int num = 0;

	// 0000 0000 0000 0000 1111 1111 1111 1111
	gdt_entries[num].low_base = (uint16_t)(base & 0xFFFF);
	// 0000 0000 1111 1111 0000 0000 0000 0000
	gdt_entries[num].mid_base = (uint8_t)(base >> 16) & 0xFF;
	// 1111 1111 0000 0000 0000 0000 0000 0000
	gdt_entries[num].base = (uint8_t)(base >> 24) & 0xFF;

	// 0000 0000 0000 0000 1111 1111 1111 1111
	gdt_entries[num].limit = (limit & 0xFFFF);
	// 0000 0000 0000 0000 1111 0000 0000 0000
	gdt_entries[num].granularity = ((limit >> 16) & 0x0F);
	gdt_entries[num].granularity |= (granularity & 0xF0);
	gdt_entries[num].access = access;

	num++;
}

void gdt_init() {
	gdt_ptr.size = ((sizeof(t_gdt_entry) * ENTRIES) - 1);
	gdt_ptr.address = (uint32_t)&gdt_entries;

	set_gdt_gate(NULL_GATE);
	set_gdt_gate(KERNEL_CODE);
	set_gdt_gate(KERNEL_DATA);
	set_gdt_gate(USER_CODE);
	set_gdt_gate(USER_DATA);

	gdt_flush((uint32_t)&gdt_ptr);
}




