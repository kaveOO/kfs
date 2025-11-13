#ifndef	VGA_H
#define	VGA_H

#include "kernel.h"

extern	unsigned char	*g_vga;
extern	unsigned char	*vga_end;

enum Colors { // https://www.fountainware.com/EXPL/vga_color_palettes.htm
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	YELLOW,
	WHITE
};

#define BLANK_CELL(g_vga) {		\
	g_vga[0] = ' ';				\
	g_vga[1] = GRAY;			\
}

#define COPY_CHAR(src, dest) {	\
	dest[0]	= src[0];			\
	dest[1]	= src[1];			\
}

void	vga_init();
void	clear_line(int line);
void	clear_screen();
void	copy_line(int src, int dest);
void	scroll_up();
void	init_header();
void	shift_chars_right(unsigned char *pos);

#endif

