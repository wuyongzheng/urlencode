#include <stdio.h>
#include <string.h>

void print_encode_char (char c)
{
	/* RFC3986:
	 * unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
	 */
	if (c >= 'A' && c <= 'Z')
		putchar(c);
	else if (c >= 'a' && c <= 'z')
		putchar(c);
	else if (c >= '0' && c <= '9')
		putchar(c);
	else if (c == '-' || c == '_' || c == '.' || c == '~')
		putchar(c);
	else
		printf("%%%02X", (unsigned int)(unsigned char)c);
}

void process_stdio (void)
{
	int c;

	while ((c = getchar()) != EOF) {
		print_encode_char((char)c);
	}
}

void print_encode_str (const char *str)
{
	while (*str) {
		print_encode_char(*str);
		str ++;
	}
}

int main (int argc, char *argv[])
{
	if (argc == 2 && (strcmp(argv[1], "-h") == 0 ||
			strcmp(argv[1], "--help") == 0)) {
		printf("Usage:\n");
		printf("1. %s val\n", argv[0]);
		printf("   Output application/x-www-form-urlencoded of val\n");
		printf("2. %s name1 val1 name2 val2 ...\n", argv[0]);
		printf("   Generate name1=val1&name2=val2 style output.\n");
		printf("   There must be even number of arguments.\n");
		printf("3. %s\n", argv[0]);
		printf("   Same as 1, but read from stdin.\n");
		return 0;
	}

	if (argc == 1)
		process_stdio();
	else if (argc == 2)
		print_encode_str(argv[1]);
	else {
		int i;
		print_encode_str(argv[1]);
		putchar('=');
		print_encode_str(argv[2]);
		for (i = 3; i + 1 < argc; i += 2) {
			putchar('&');
			print_encode_str(argv[i]);
			putchar('=');
			print_encode_str(argv[i + 1]);
		}
	}

	return 0;
}
