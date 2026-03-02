#ifndef GDT_H
#define GDT_T

#include "types.h"

#define ENTRIES 5

#define NULL_GATE	0, 0x00000000, 0x00, 0x0

#define KERNEL_CODE	0, 0xFFFFF, 0x9A, 0xC0
#define KERNEL_DATA	0, 0xFFFFF, 0x92, 0xC0

#define USER_CODE	0, 0xFFFFF, 0xFA, 0xC0
#define USER_DATA	0, 0xFFFFF, 0xF2, 0xC0

// https://staktrace.com/nuggets/index.php?id=11
typedef struct s_gdt_entry {
	uint16_t	limit;
	uint16_t	low_base;
	uint8_t		mid_base;
	uint8_t		access;
	uint8_t		granularity;
	uint8_t		base;
} __attribute__((packed)) t_gdt_entry;

typedef struct s_gdt_ptr {
	uint16_t	size;
	uint32_t	address;
} __attribute__((packed)) t_gdt_ptr;

void gdt_init();

#endif
