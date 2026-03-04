#include "kernel.h"

unsigned char *video = VGA_ENTRY;
unsigned char *end = VGA_END;

void kmain() {
	vga_init();
	// gdt_init();
	// keyboard_poll_loop();
	// while (1) {
	// 	printk(RED, "gdt init sucessfull !\a\a");
	// }
}
