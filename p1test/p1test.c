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


#define MODULE_NAME "p1test"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

static int __init hello_init(void)
{
    pr_info("%s init\n", MODULE_NAME);    
    // kasan addr
    char* addr = 0xffffec0000000000;
    int i = 0;
    for (i = 0;i < 10;i++) {
        pr_info("%c\n", addr[i]);
    }
    pr_info("%s cout\n", MODULE_NAME);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003