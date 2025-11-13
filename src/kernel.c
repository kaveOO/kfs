#include "kernel.h"

unsigned char *video = VGA_ENTRY;
unsigned char *end = VGA_END;

void kmain() {
	vga_init();
	keyboard_poll_loop();
}
