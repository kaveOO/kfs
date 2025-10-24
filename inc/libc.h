#ifndef LIBC_H
#define LIBC_H

#include "writek.h"

int putchark(int c, unsigned int color);
int putstrk(const char *str, unsigned int color);
int strlenk(const char *str);

#endif
