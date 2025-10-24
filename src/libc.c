#include "libc.h"

int strlenk(const char *str) {
	int	i = 0;

	while (str[i]) {
		i++;
	}
	return i;
}

int putchark(int c, unsigned int color) {
	return writek(c, 1, color);
}

int putstrk(const char *str, unsigned int color) {
	int len = strlenk(str);

	for (int i = 0; i < len; i++) {
		writek(str[i], 1, color);
	}
	return len;
}
