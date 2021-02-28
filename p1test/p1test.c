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

unsigned long getvCR3(int pid) 
{
    struct task_struct *task;
    struct mm_struct *mm;
    unsigned long cr3;

    task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
    if (task == NULL) 
        return 0;
    mm = task->mm;
    if (mm == NULL)
        mm = task->active_mm;
    if (mm == NULL)
        return 0;
    cr3 = mm->pgd;
    return cr3;
}


static int __init hello_init(void)
{
    int i;
    unsigned long cr3;
    
    pgd_t* pgds;
    pr_info("%s init\n", MODULE_NAME);  
    
    cr3 = getvCR3(current->pid);
    pr_info("cr3 : %lx\n", cr3);
    pgds = (pgd_t*) kmalloc(4096, GFP_KERNEL);
    pr_info("kmalloc pgds:%lx\n", pgds);
    pgds = cr3;
    pr_info("pgds: %lx\n", pgds);
    for (i = 0;i < 512;i++) {
        pr_info("pgd[%d]: %lx  %lx  %lx\n", i, &pgds[i], pgds[i], (0xffff000000000000 + (i << 39)));
    }

    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003

// 18446612682070032000-18446744073692774000  =  131391622742000
// 1024*1024*1024*1024 = 1099511627776

// 131391622742000/1099511627776 = 119
// 119 / 8 = 14

// 18446603336221196000-18446744073692774000
// -140737471578000
// 140737471578000/1099511627776
// 127
// 127/8
// 15