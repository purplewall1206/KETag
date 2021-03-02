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

#include <linux/ketag.h>


#define MODULE_NAME "p2test"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");


static int __init hello_init(void)
{
    pr_info("%s init\n", MODULE_NAME);    
    unsigned long addr = 0xffffffffffffffff;
    // void (*target)(unsigned long );
    // target = (void *)0xffffffff812a8b09;
    // (*target)(addr);
    alloc_ketag_startpage(addr);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003