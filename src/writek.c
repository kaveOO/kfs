#include "writek.h"

static int HandleEscapeCharacters(char c)
{
	switch (c)
	{
		case '\n':
		{
			video += (80 * 2) - ((video - VGA_ENTRY) % (80 * 2)); // Move at the start of NL
			return 1;
		}
		case '\t':
		{
			// TODO handle tab in video buffer
		}
	}
    return 0;
}

void writek(unsigned int colour, const char *str, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (HandleEscapeCharacters(str[i]) == 1)
		{
			continue;
		}
		*video++ = str[i];
		*video++ = colour;
	}
	UpdateCursor();
}
