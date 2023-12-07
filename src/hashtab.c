#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashtab.h>

unsigned int hashtab_hash_KRHash(char* key, int size)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % size;
}

unsigned int hashtab_hash_ELFHash(char* key, int size)
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

void hashtab_init(struct listnode** hashtab, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        hashtab[i] = NULL;
    }
}

void hashtab_add(struct listnode** hashtab, char* key, int value, int size)
{
    struct listnode* node;
    int index = hashtab_hash_ELFHash(key, size);
    node = (struct listnode*)malloc(sizeof(*node));
    node->key = (char*)malloc(sizeof(char) * 30);
    if (node != NULL && node->key != NULL) {
        strcpy(node->key, key);
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode* hashtab_lookup(struct listnode** hashtab, char* key, int size)
{
    struct listnode* node;
    int index = hashtab_hash_ELFHash(key, size);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0)
            return node;
    }
    return NULL;
}

void hashtab_delete(struct listnode** hashtab, char* key, int size)
{
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash_ELFHash(key, size);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL) {
                hashtab[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
}

void hashtab_free(struct listnode** hashtab, int size)
{
    int i;
    struct listnode *node, *next = NULL;
    for (i = 0; i < size; i++) {
        // printf("-%d-", i);
        while (hashtab[i] != NULL) {
            node = hashtab[i];
            if (hashtab[i]->next != NULL) {
                next = node->next;
            }
            free(node->key);
            free(node);
            hashtab[i] = next;
            next = NULL;
        }
    }
    // if(size)
    free(hashtab);
}

void hashtab_print(struct listnode** hashtab, int size)
{
    int i;
    struct listnode* node;
    for (i = 0; i < size; i++) {
        if (hashtab[i] == NULL) {
            printf("Node[%d]: NULL\n\n", i);
            continue;
        }
        node = hashtab[i];
        printf("Node[%d]: %s, %d\n", i, node->key, node->value);
        while (node->next != NULL) {
            node = node->next;
            printf("Node[%d]: %s, %d\n", i, node->key, node->value);
        }
        printf("\n");
    }
}
