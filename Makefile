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

.PHONY: bin/test1

bin/test1: testpart/test1.c libs/bloom_filter.so libs/hashtab.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

.PHONY: bin/test2

bin/test2: testpart/test2.c libs/bloom_filter.so libs/hashtab.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

.PHONY: bin/test3

bin/test3: testpart/test3.c libs/bloom_filter.so libs/hashtab.so
	$(CC) $(CFLAGS) $(LIBS) -Wl,-rpath=libs/ -o $@ $^

.SILENT: clean

clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.tmp" -exec rm -f {} \;
	rm -rf bin/bloom_filter
	rm -rf bin/test1
	rm -rf bin/test2
	rm -rf bin/test3

rebuild: clean all

clean_test1:
	rm -rf bin/test1

clean_test2:
	rm -rf bin/test2

clean_test3:
	rm -rf bin/test3

run:
	bin/bloom_filter

memory_check:
	valgrind --leak-check=full bin/bloom_filter

run_test1:
	bin/test1

run_test2:
	bin/test2

run_test3:
	bin/test3