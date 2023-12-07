#include <stdio.h>
#include <hashtab.h>
#include <bloom_filter.h>

int main()
{
    struct bloom_filter* bf = bloom_filter_init(5051, 200);
    bloom_filter_test_ip(bf);

    char* ip = "192.168.1.200";
    if (bloom_filter_lookup(bf, ip) == 0)
        printf("Этого ip(%s) нет в множестве\n", ip);

    // bloom_filter_print(bf);
    bloom_filter_free(bf);
    return 0;
}
