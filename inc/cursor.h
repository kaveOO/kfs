#ifndef CURSOR_H
#define CURSOR_H

#include "kernel.h"

#define	CURSOR_CMD	0x3D4
#define	CURSOR_DATA	0x3D5

void	move_cursor();
void	update_cursor(int row, int col);

#endif
