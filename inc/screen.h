#ifndef SCREEN_H
#define SCREEN_H

#include "kernel.h"

typedef struct s_screen {
	int				cursor_row;
	int				cursor_col;
	unsigned int 	theme;
	bool			switched;
	unsigned char	buffer[VGA_SIZE];
} t_screen;

extern t_screen		g_screens[13];
extern unsigned int	g_current_screen;

void screen_changer(uint8_t key);
void init_screens();

#endif
