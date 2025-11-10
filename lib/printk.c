#include "lib.h"

int putnbrk(int nb, unsigned int color) {
	int count = 0;

	if (nb < 0) {
		count += writek('-', 1, color);
		nb = -nb;
	} else if (nb < 10) {
		count += writek(nb + '0', 1, color);
	} else {
		count += putnbrk(nb / 10, color);
		count += putnbrk(nb % 10, color);
	}
	return count;
}

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
					// Fallthrough
				case 's':
					count += putstrk(va_arg(list, const char *), color);
					// Fallthrough
				case 'd':
					count += putnbrk(va_arg(list, int), color);
			}
			continue;
		}
		count += writek(str[i], 1, color);
	}
	return count;
}
