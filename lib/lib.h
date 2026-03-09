#ifndef LIB_H
#define LIB_H

#include "kernel.h"

int		putchark(int c, unsigned int color);
int		putstrk(const char *str, unsigned int color);
int		strlenk(const char *str);
int		writek(int c, int len, unsigned int color);
int		printk(unsigned int color, const char *str, ...);
int		strncmpk(const char *s1, const char *s2, unsigned int n);
void	*memsetk(void *ptr, int value, unsigned long num);
int		strcmpk(const char *s1, const char *s2);

#endif
