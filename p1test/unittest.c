#include <stdio.h>

int main()
{   
    int total = 0x7ffffc00;
    printf("%xKB, %dMB, %dGB\n", total/1024, total/(1<<20), total/(1<<30));
    return 0;
}