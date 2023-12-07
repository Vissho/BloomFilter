#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
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
    int hashsize = 500001;
    double t1, t2, t3, t4;
    struct listnode** hashtab;
    struct bloom_filter* bf;
    char str[30];
    for (int i = 0; i < step && step != 1100000; i++) {
        if (i == 0) {
            bf = bloom_filter_init(step, step);
            hashtab = (struct listnode**)malloc(
                    sizeof(struct lisnode*) * hashsize);
            hashtab_init(hashtab, hashsize);
        }

        sprintf(str, "%d", i);
        hashtab_add(hashtab, str, i, hashsize);
        bloom_filter_add(bf, str);
        str[0] = '\0';

        if (i == step - 1) {
            struct listnode* temp;
            int col1 = 0, col2 = 0, t = 1;

            t1 = wtime();
            for (int j = 0; j < step; j++) {
                sprintf(str, "%d", j * t);
                temp = hashtab_lookup(hashtab, str, hashsize);
                if (temp) {
                    col1++;
                }
                str[0] = '\0';
                t = t * (-1);
            }
            t2 = wtime() - t1;

            t = 1;
            t3 = wtime();
            for (int j = 0; j < step; j++) {
                sprintf(str, "%d", j * t);
                if (bloom_filter_lookup(bf, str)) {
                    col2++;
                }
                str[0] = '\0';
                t = t * (-1);
            }
            t4 = wtime() - t3;

            printf("%d %lf %lf %d %d\n", step, t2, t4, col2, col1);

            bloom_filter_free(bf);
            hashtab_free(hashtab, hashsize);
            i = -1;
            step += 100000;
        }
    }

    return 0;
}
