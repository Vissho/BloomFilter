#include <bloom_filter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash_function_KRHash(char* key, int size)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % size;
}

unsigned int hash_function_ELFHash(char* key, int size)
{
    unsigned int h = 0, g;
    while (*key) {
        h = (h << 4) + (unsigned int)*key++;
        g = h & 0xF0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h % size;
}

struct bloom_filter* bloom_filter_init(int size, int number_expected_elements)
{
    struct bloom_filter* bf
            = (struct bloom_filter*)malloc(sizeof(struct bloom_filter));
    if (!bf)
        return NULL;
    bf->size = size;
    bf->number_expected_elements = number_expected_elements;
    bf->array = (int*)calloc(sizeof(int), size);
    if (!bf->array) {
        free(bf);
        return NULL;
    }
    return bf;
}

void bloom_filter_test_ip(struct bloom_filter* bf)
{
    for (int i = 0; i < bf->number_expected_elements; i++) {
        char str[12];
        char ip[24];

        strcat(ip, "192.168.1.");
        sprintf(str, "%d", i);
        strcat(ip, str);
        bloom_filter_add(bf, ip);

        str[0] = '\0';
        ip[0] = '\0';
    }
}

void bloom_filter_add(struct bloom_filter* bf, char* key)
{
    bf->array[hash_function_KRHash(key, bf->size)] = 1;
    bf->array[hash_function_ELFHash(key, bf->size)] = 1;
}

int bloom_filter_lookup(struct bloom_filter* bf, char* key)
{
    if (bf->array[hash_function_KRHash(key, bf->size)] == 0
        || bf->array[hash_function_ELFHash(key, bf->size)] == 0)
        return 0;
    return 1;
}

void bloom_filter_print(struct bloom_filter* bf)
{
    int i;
    for (i = 0; i < bf->size; i++) {
        if (bf->array[i] == 1) {
            printf("Node[%d]: %d\n", i, bf->array[i]);
            printf("\n");
        }
    }
}

void bloom_filter_free(struct bloom_filter* bf)
{
    if (bf && bf->array) {
        free(bf->array);
        free(bf);
    }
}
