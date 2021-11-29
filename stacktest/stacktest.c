#include <linux/mm.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/io.h>
#include <linux/kernel.h>
#include <asm/processor.h>
#include <asm/pgtable_64.h>
#include <linux/mm_types.h>
#include <linux/pgtable.h>
#include <linux/slab.h>
#include <linux/hugetlb.h>
#include <asm/pgtable.h>


#define MODULE_NAME "stacktest"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

static int __init stacktest_init(void)
{
    int a;
    int b;
    a = 1000;
    b = 666;
    // unsigned long *value = (unsigned long)(0x00008000000);
    pr_info("%s init\n", MODULE_NAME);    
    pr_info("stack : %016lx\n", (unsigned long )current->stack);
    pr_info("a: %d  %016lx\n", a, (unsigned long)&a);
    pr_info("b: %d  %016lx\n", b, (unsigned long)&b);
    pr_info("distance: %016lx  %016lx\n", (unsigned long)&a-(unsigned long )current->stack,
            (unsigned long)&b- (unsigned long )current->stack);
    // pr_info("user space : %016lx\n", value[0]);
    return 0;
}

static void __exit stacktest_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(stacktest_init);
module_exit(stacktest_exit);

// 79b7c000   79b7c003