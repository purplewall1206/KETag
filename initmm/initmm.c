#include <linux/mm.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

#include <linux/slab.h>


#define MODULE_NAME "initmm"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

static int __init hello_init(void)
{
    struct mm_struct *mm;

    pr_info("%s init\n", MODULE_NAME);   
    
    mm = (struct mm_struct*)0xffffffff826f3a60; 
    pr_info("initmm   pgd:%lx  %lx\n", mm->pgd, pgd_val(*(mm->pgd)));

    pr_info("vma %lx\n", mm->mmap);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003