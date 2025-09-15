#include "kernel.h"

void kmain(void);

void WriteString(int colour, const char *string)
{
	char *video = (char *)0xB8000;

	while(*string)
	{
		*video++ = *string++;
		*video++ = colour;
	}
}

void kmain(void)
{
	WriteString(VGA_PURPLE, "42");
}
