#include "writek.h"

void EraseChar()
{
    if (video > VGA_ENTRY) // Check for the VGA start
	{
        video -= 2;
        *video = ' ';
        *(video + 1) = 7;
    }
}

static int HandleEscapeCharacters(char c)
{
	switch (c)
	{
		case '\n':
		{
			video += (VGA_LINE) - ((video - VGA_ENTRY) % (VGA_LINE)); // Move at the start of NL
			return 1;
		}
		case '\t':
		{
			video += 4; // Size of the tab
			return 1;
		}
		case '\b':
		{
			EraseChar();
			return 1;
		}
		case '\a':
		{
			beep();
			return 1;
		}
		case '\r':
		{
			video -= (video - VGA_ENTRY);
			return 1;
		}
		case '\v':
		{
			video += VGA_LINE;
			return 1;
		}
	}
    return 0;
}

void writek(unsigned int colour, const char *str, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (HandleEscapeCharacters(str[i]))
			continue;
		if (video == end)
		{
			beep();
		}
		*video++ = str[i];
		*video++ = colour;
	}
	UpdateCursor();
}
