#include "kernel.h"
#include "types.h"
#include "cursor.h"
#include "io.h"

void WriteString(int colour, const char *string)
{
	char *video = (char *)VGA_ENTRY;

	while(*string)
	{
		*video++ = *string++;
		*video++ = colour;
	}
}

void kmain(void)
{
	WriteString(VGA_PURPLE, "42 This is mandatory");
	// disable_cursor();
	// UpdateCursor(10, 0);
}
