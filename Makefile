.PHONY: all
all: urlencode urldecode

urlencode: urlencode.c

urldecode: urldecode.c

.PHONY: clean
clean:
	rm -f urlencode urldecode
