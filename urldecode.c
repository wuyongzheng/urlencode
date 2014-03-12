#include <stdio.h>
#include <string.h>

/* returns number of characters parsed in str,
 * because there can be leftover when partial input, e.g. abc%3 or abc%
 * Bad input is silently ignored. */
static int decode_string (const char *str)
{
	int inptr = 0;
	while (1) {
		int c;
		switch (str[inptr]) {
		case 0:
			return inptr;
		case '%':
			if ('0' <= str[inptr+1] && str[inptr+1] <= '9')
				c = str[inptr+1] - '0';
			else if ('a' <= str[inptr+1] && str[inptr+1] <= 'f')
				c = str[inptr+1] - 'a' + 10;
			else if ('A' <= str[inptr+1] && str[inptr+1] <= 'F')
				c = str[inptr+1] - 'A' + 10;
			else if (str[inptr+1] == 0)
				return inptr;
			else {
				inptr += 1;
				break;
			}
			c *= 16;
			if ('0' <= str[inptr+2] && str[inptr+2] <= '9')
				c += str[inptr+2] - '0';
			else if ('a' <= str[inptr+2] && str[inptr+2] <= 'f')
				c += str[inptr+2] - 'a' + 10;
			else if ('A' <= str[inptr+2] && str[inptr+2] <= 'F')
				c += str[inptr+2] - 'A' + 10;
			else if (str[inptr+2] == 0)
				return inptr;
			else {
				inptr += 2;
				break;
			}
			putchar(c);
			inptr += 3;
			break;
		case '+':
			putchar(' ');
			inptr ++;
			break;
		case '\r':
		case '\n':
			inptr ++;
			break;
		default:
			putchar(str[inptr]);
			inptr ++;
			break;
		}
	}
	return inptr;
}

#define BUFFERSIZE 4000
static void process_stdio (void)
{
	char buffer[BUFFERSIZE];
	int leftover = 0;

	while (!feof(stdin)) {
		int readlen, strleng, parselen, lastround;

		readlen = fread(buffer + leftover, 1, BUFFERSIZE - 1 - leftover, stdin);
		if (readlen <= 0)
			break;
		lastround = (readlen < BUFFERSIZE - 1 - leftover);
		strleng = leftover + readlen;
		buffer[strleng] = '\0';
		parselen = decode_string(buffer);
		leftover = strleng - parselen;
		if (leftover)
			memcpy(buffer, buffer + parselen, strleng - parselen);
		if (lastround)
			break;
	}
}

static void print_decode_str (const char *str)
{
	decode_string(str);
}

int main (int argc, char *argv[])
{
	if (argc == 2 && (strcmp(argv[1], "-h") == 0 ||
			strcmp(argv[1], "--help") == 0)) {
		printf("Usage: %s [str]\n");
		printf("   str: application/x-www-form-urlencoded string\n");
		printf("   If str is not given, read from stdin (ignoring all new line characters)\n");
		return 0;
	}

	if (argc == 1)
		process_stdio();
	else
		print_decode_str(argv[1]);

	return 0;
}
