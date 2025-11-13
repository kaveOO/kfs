#include "kernel.h"

unsigned char *video = VGA_ENTRY;
unsigned char *end = VGA_END;

void kmain() {
	vga_init();
	printk(RED, "%d\n test", 2147483648);
	// keyboard_poll_loop();
}
