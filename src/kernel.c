#include "kernel.h"
#include "types.h"
#include "cursor.h"
#include "io.h"
#include "writek.h"
#include "song.h"

char *video = VGA_ENTRY;

void kmain(void)
{
	// beep();
	// WriteString(VGA_PURPLE, "42 This is mandatory");
	// writek(VGA_PURPLE, "LnKKK est le goat\a", 18);
	writek(VGA_PURPLE, "jer\r", 4);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// disable_cursor();
	// UpdateCursor(10, 0);
}
