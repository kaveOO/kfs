#ifndef KERNEL_H
#define KERNEL_H

#define	VGA_WIDTH		80
#define	VGA_HEIGHT		25
#define	VGA_ENTRY		(unsigned char *) 0xB8000
#define	VGA_LINE		VGA_WIDTH * 2
#define	VGA_SIZE		(VGA_WIDTH * VGA_HEIGHT) * 2
#define	VGA_END			VGA_ENTRY + VGA_SIZE

#include "lib.h"
#include "vga.h"
#include "types.h"
#include "stdarg.h"
#include "song.h"
#include "cursor.h"
#include "io.h"
#include "keyboard.h"
#include "theme.h"
#include "screen.h"

#endif
