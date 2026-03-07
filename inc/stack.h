#ifndef STACK_H
#define STACK_H

#define DUMP_SIZE 16 // 8 or 16

extern uint32_t	stack_top[];
extern uint32_t	stack_bottom[];

static inline uint32_t get_esp() {
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	return esp;
}

static inline uint32_t get_ebp() {
	uint32_t ebp;
	asm volatile("mov %%ebp, %0" : "=r"(ebp));
	return ebp;
}

void hexdump(unsigned char *start, unsigned char *end);

#endif
