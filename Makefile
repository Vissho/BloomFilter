CC = gcc

CFLAGS = -g3 -O0 -Wall -Wextra -Werror -fPIC
LIBS = -I include/

.PHONY: all

all: bin/bloom_filter libs/bloom_filter.so

bin/bloom_filter: src/main.c libs/bloom_filter.so libs/hashtab.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

libs/bloom_filter.so: src/bloom_filter.c
	$(CC) $(CFLAGS) -shared $(LIBS) -o $@ $^

libs/hashtab.so: src/hashtab.c
	$(CC) $(CFLAGS) -shared $(LIBS) -o $@ $^

.SILENT: clean

clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.tmp" -exec rm -f {} \;
	rm -rf bin/bloom_filter

rebuild: clean all

run:
	bin/bloom_filter

memory_check:
	valgrind --leak-check=full bin/bloom_filter
