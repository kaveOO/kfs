#ifndef LIB_H
#define LIB_H

#include "kernel.h"
#include "stdarg.h"
#include "song.h"
#include "cursor.h"

int putchark(int c, unsigned int color);
int putstrk(const char *str, unsigned int color);
int strlenk(const char *str);
int writek(int c, unsigned int len, unsigned int color);
int printk(int color, const char *str, ...);

#endif
