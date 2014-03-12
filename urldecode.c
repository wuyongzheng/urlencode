#include <stdio.h>
#include <stdlib.h>

void print_decode_str (const char *str)
{
	const char *ptr = str;

	while (*ptr) {
		int c1, c2;
		switch (*ptr) {
		case '%':
			c1 = *(++ ptr);
			c2 = *(++ ptr);
			if (c1 == 0 || c2 == 0)
				return;
			if (c1 >= '0' && c1 <= '9')
				c1 -= '0';
			else if (c1 >= 'a' && c1 <= 'f')
				c1 -= 'a' - 10;
			else if (c1 >= 'A' && c1 <= 'F')
				c1 -= 'A' - 10;
			else
				return;
			if (c2 >= '0' && c2 <= '9')
				c2 -= '0';
			else if (c2 >= 'a' && c2 <= 'f')
				c2 -= 'a' - 10;
			else if (c2 >= 'A' && c2 <= 'F')
				c2 -= 'A' - 10;
			else
				return;
			putchar(c1 * 16 + c2);
			break;
		case '+':
			putchar(' ');
			break;
		default:
			putchar(*ptr);
		}
		ptr ++;
	}
}

void process_stdio (void)
{
	char *buffer = NULL;
	int cap = 0, length = 0;

	while (!feof(stdin)) {
		cap = cap * 2 + 8192;
		buffer = (char *)realloc(buffer, cap);
		length += fread(buffer + length, 1, cap - length - 1, stdin);
	}

	buffer[length] = '\0';

	print_decode_str(buffer);
	free(buffer);
}

int main (int argc, char *argv[])
{
	if (argc == 1)
		process_stdio();
	else
		print_decode_str(argv[1]);

	return 0;
}
