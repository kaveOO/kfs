#include "kernel.h"
#include "types.h"
#include "cursor.h"
#include "io.h"
#include "writek.h"
#include "printk.h"
#include "song.h"

char	*video	= VGA_ENTRY;
char	*end	= VGA_END;

// TODO -pedantic -Wconversion flags implementation

void kmain() {
	// beep();
	// WriteString(VGA_PURPLE, "42 This is mandatory");
	// writek(VGA_PURPLE, "LnKKK est le goat\a", 18);
	printk(VGA_PURPLE, "%s", "ttest");
	// writek(VGA_PURPLE, "te\n", 3);
	// writek(VGA_PURPLE, "je\n", 3);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// writek(VGA_PURPLE, "LnKKK est le goat\n", 18);
	// disable_cursor();
	// UpdateCursor(10, 0);
}
