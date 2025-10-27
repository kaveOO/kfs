#ifndef VGA_H
#define VGA_H

#include "kernel.h"

#define VGA_WIDTH	80
#define VGA_HEIGHT	25

#define HEADER		true

#define	VGA_ENTRY	(unsigned char *) 0xB8000
#define VGA_LINE	VGA_WIDTH * 2
#define VGA_SIZE	(VGA_WIDTH * VGA_HEIGHT) * 2 // Total size of VGA screen
#define VGA_END		VGA_ENTRY + VGA_SIZE

extern unsigned char	*vga;
extern unsigned char	*vga_end;

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

#define ERASE_CHAR(vga) {		\
	vga[0] = ' ';				\
	vga[1] = GRAY;				\
}

#define COPY_CHAR(src, dest) {	\
	dest[0]	= src[0];			\
	dest[1]	= src[1];			\
}

void vga_init();
void clear_line(int line);
void clear_screen();
void copy_line(int src, int dest);
void scroll_up();

#endif

