#ifndef KERNEL_H
#define KERNEL_H

#define WIDTH	80
#define HEIGHT	25

#define	VGA_ENTRY	(char *) 0xB8000
#define VGA_LINE	WIDTH * 2
#define VGA_SIZE	(WIDTH * HEIGHT) * 2 // Total size of VGA screen
#define VGA_END		VGA_ENTRY + VGA_SIZE;

extern char *video;
extern char *end;

enum VGAColors	//  Video Graphics Array
{
	VGA_BLACK,
	VGA_BLUE,
	VGA_GREEN,
	VGA_CYAN,
	VGA_RED,
	VGA_PURPLE,
	VGA_BROWN,
	VGA_GRAY,
	VGA_DARK_GRAY,
	VGA_LIGHT_BLUE,
	VGA_LIGHT_GREEN,
	VGA_LIGHT_CYAN,
	VGA_LIGHT_RED,
	VGA_LIGHT_PURPLE,
	VGA_YELLOW,
	VGA_WHITE,
};

#endif
