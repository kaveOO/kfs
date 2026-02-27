#ifndef GDT_H
#define GDT_T

#include "types.h"

// https://staktrace.com/nuggets/index.php?id=11
struct gdt_entry {
	uint16_t	limit;
	uint16_t	low_base;
	uint8_t		med_base;
	uint8_t		access;
	uint8_t		granularity;
	uint8_t		base;
}__attribute__((packed));

#endif
