#ifndef _HASHTAB_H_
#define _HASHTAB_H_
#define HASH_SIZE 5051

struct listnode {
    char* key;
    int value;
    struct listnode* next;
};

// struct listnode *hashtab[HASH_SIZE];

unsigned int hashtab_hash_KRHash(char* key, int size);
unsigned int hashtab_hash_ELFHash(char* key, int size);
void hashtab_init(struct listnode** hashtab, int size);
void hashtab_add(struct listnode** hashtab, char* key, int value, int size);
struct listnode* hashtab_lookup(struct listnode** hashtab, char* key, int size);
void hashtab_delete(struct listnode** hashtab, char* key, int size);
void hashtab_free(struct listnode** hashtab, int size);
void hashtab_print(struct listnode** hashtab, int size);

#endif //  _HASHTAB_H_
