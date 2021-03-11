#include <stdio.h>

// #define ketag_get_rbp()    { unsigned long rbp = 0; asm("movq %%rbp, %0":"=r"(rbp)); printf("%016lx\n", rbp); return rbp; }


#define \
    foo(x) \
    ({ \
        int xx = (x); \
        int result = (xx > 32) ? xx : (2*xx); \
        result; \
    })

#define \
    ketag_get_rbp() \
    ({ \
        unsigned long rbp = 0x0; \
        asm("movq %%rbp, %0\n\t" \
            : "=r"(rbp)); \
        rbp; \
    })

void getrbp()
{
    unsigned long rbp = 0x0;
    asm("movq %%rbp, %0\n\t"
        : "=r"(rbp));
    printf("%016lx\n", rbp);
}

int main()
{
    printf("%d\n", foo(10));
    printf("%016lx\n", ketag_get_rbp());
    // getrbp();
    unsigned long rbp = 0x0;
    asm("movq %%rbp, %0\n\t"
        : "=r"(rbp));
    printf("%016lx\n", rbp);
    // getrbp();
    // ketag_get_rbp();
    // unsigned long x = ketag_get_rbp();
    // printf("%016lx\n", x);
    return 0;
}