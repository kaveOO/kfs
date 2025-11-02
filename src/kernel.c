#include "kernel.h"
#include "types.h"
#include "cursor.h"
#include "io.h"
#include "song.h"
#include "keyboard.h"

unsigned char *video = VGA_ENTRY;
unsigned char *end = VGA_END;

void kmain()
{
	vga_init();
	// If IRQs/IDT are not yet implemented, use the polling fallback to see keyboard input
	keyboard_poll_loop();
}
