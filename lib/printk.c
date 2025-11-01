#include "lib.h"

int printk(unsigned int color, const char *str, ...) {
	va_list list;
	va_start(list, str);

	int count = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == '%') {
			i++;
			switch (str[i]) {
				case 'c':
					count += putchark(va_arg(list, int), color);
					break;
				case 's':
					count += putstrk(va_arg(list, const char *), color);
			}
			continue;
		}
		count += writek(str[i], 1, color);
	}
	return count;
}
