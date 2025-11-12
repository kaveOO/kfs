#ifndef SCREEN_H
#define SCREEN_H

#include "kernel.h"

typedef struct s_screen {
	int				cursor_row;
	int				cursor_col;
	bool			switched;
	unsigned char	buffer[VGA_SIZE];
} t_screen;

static const uint8_t key_to_screen_map[0x59] = {
	[0x3B] = 1,
	[0x3C] = 2,
	[0x3D] = 3,
	[0x3E] = 4,
	[0x3F] = 5,
	[0x40] = 6,
	[0x41] = 7,
	[0x42] = 8,
	[0x43] = 9,
	[0x44] = 10,
	[0x57] = 11,
	[0x58] = 12
};

extern t_screen		g_screens[13];
extern unsigned int	g_current_screen;

void screen_changer(uint8_t key);
void init_screens();

#endif
