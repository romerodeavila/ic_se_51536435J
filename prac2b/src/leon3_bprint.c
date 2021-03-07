#include "leon3_bprint.h"

int8_t leon3_print_string(char* str) {
	uint32_t e = 0;
	int i = 0;

	while (str[i] != '\0' && e == 0) {
		//Si la cadena no se ha acabado
		e += leon3_putchar(str[i]);
		i++;
	}

	return e;
}

int8_t leon3_print_uint8(uint8_t i) {
	uint32_t e = 0;
	char c;
	int cen, dec, uni;

	while (i > 0 && (!e)) {

		if (i >= 100) {
			cen = i / 100;
			i -= 100 * cen;
			c = cen + '0';
			e += leon3_putchar(c);

			dec = i / 10;
			i -= 100 * dec;
			c = dec + '0';
			e += leon3_putchar(c);

			uni = i;
			i -= uni;
			c = uni + '0';
			e += leon3_putchar(c);
		} else if (i >= 10) {

			dec = i / 10;
			i -= 10 * dec;
			c = dec + '0';
			e += leon3_putchar(c);

			uni = i;
			i -= uni;
			c = uni + '0';
			e += leon3_putchar(c);
		} else {
			uni = i;
			i -= uni;
			c = uni + '0';
			e += leon3_putchar(c);
		}
	}
}

