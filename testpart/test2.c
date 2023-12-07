#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <hashtab.h>
#include <bloom_filter.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    int step = 100000;
    double t1, t2, t3, t4;
    struct listnode** hashtab;
    struct bloom_filter* bf;
    char str[30];
    for (int i = 0; i < step && step != 1100000; i++) {
        if (i == 0) {
            bf = bloom_filter_init(step, step);
            hashtab = (struct listnode**)malloc(sizeof(struct lisnode*) * step);
            hashtab_init(hashtab, step);
        }

        sprintf(str, "%d", i);
        hashtab_add(hashtab, str, i, step);
        bloom_filter_add(bf, str);
        str[0] = '\0';

        if (i == step - 1) {
            struct listnode* temp;

            t1 = wtime();
            for (int j = 0; j < step; j++) {
                sprintf(str, "%d", j);
                temp = hashtab_lookup(hashtab, str, step);
                if (strcmp(temp->key, str)) {
                    printf("Error!\n");
                    break;
                }
                str[0] = '\0';
            }
            t2 = wtime() - t1;

            t3 = wtime();
            for (int j = 0; j < step; j++) {
                sprintf(str, "%d", j);
                if (!bloom_filter_lookup(bf, str)) {
                    printf("Error!\n");
                    break;
                }
                str[0] = '\0';
            }
            t4 = wtime() - t3;

            printf("%d %lf %lf\n", step, t2, t4);

            bloom_filter_free(bf);
            hashtab_free(hashtab, step);
            i = -1;
            step += 100000;
        }
    }

    return 0;
}
