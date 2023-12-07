#ifndef BLOOM_FILTER
#define BLOOM_FILTER

typedef struct bloom_filter {
    int size;
    int number_expected_elements;
    int* array;
} bf;

unsigned int hash_function_KRHash(char* key, int size);
unsigned int hash_function_ELFHash(char* key, int size);
struct bloom_filter* bloom_filter_init(int size, int number_expected_elements);
void bloom_filter_test_ip(struct bloom_filter* bf);
void bloom_filter_add(struct bloom_filter* bf, char* key);
int bloom_filter_lookup(struct bloom_filter* bf, char* key);
void bloom_filter_print(struct bloom_filter* bf);
void bloom_filter_free(struct bloom_filter* bf);

#endif //  BLOOM_FILTER
