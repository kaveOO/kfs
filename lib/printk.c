#include "lib.h"

static int print_hex_up(unsigned int nb, unsigned int color) {
	int count = 0;
	char *hex = "0123456789ABCDEF";

	if (nb >= 16) {
		count += print_hex_up(nb / 16, color);
	}
	count += putchark(hex[nb % 16], color);
	return count;
}

static int print_hex_low(unsigned int nb, unsigned int color) {
	int count = 0;
	char *hex = "0123456789abcdef";

	if (nb >= 16) {
		count += print_hex_low(nb / 16, color);
	}
	count += putchark(hex[nb % 16], color);
	return count;
}

static int putnbrk(int nb, unsigned int color) {
	int count = 0;

	if (nb == -2147483648) {
		count += putstrk("-2147483648", color);
		return count;
	} else if (nb < 0) {
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
					break;
				case 's':
					count += putstrk(va_arg(list, const char *), color);
					break;
				case 'd':
				case 'i':
					count += putnbrk(va_arg(list, int), color);
					break;
				case 'x':
					count += print_hex_low(va_arg(list, unsigned int), color);
					break;
				case 'X':
					count += print_hex_up(va_arg(list, unsigned int), color);
					break;
			}
			i++;
		}
		count += writek(str[i], 1, color);
	}
	va_end(list);
	return count;
}
