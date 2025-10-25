#include "lib.h"

int putstrk(const char *str, unsigned int color) {
	int len = strlenk(str);

	for (int i = 0; i < len; i++) {
		writek(str[i], 1, color);
	}
	return len;
}
