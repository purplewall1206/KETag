#include <stdio.h>

int main()
{   
    unsigned long total = 0xc0000000;
    printf("%d . %dKB, %d . %dMB, %d . %dGB\n", total/1024, total%1024, total/(1<<20), total%(1<<20), total/(1<<30), total % (1<<30));
    return 0;
}