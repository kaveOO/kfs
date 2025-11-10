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

// TODO Rename variables here (bullshit name)
typedef struct screen {
	unsigned char buffer[VGA_SIZE + 1];
	int cursor_row;
	int cursor_column;
} t_screen;

extern t_screen save[10];
extern unsigned int current_screen;
extern unsigned int g_cursor_col;
extern unsigned int g_cursor_row;

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

enum Screens {
	SCREEN_1,
	SCREEN_2,
	SCREEN_3,
	SCREEN_4,
	SCREEN_5,
	SCREEN_6,
	SCREEN_7,
	SCREEN_8,
	SCREEN_9,
	SCREEN_10,
	SCREEN_11,
	SCREEN_12
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

#include "types.h"

void screen_changer(uint8_t key);

#endif

