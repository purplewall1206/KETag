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
#include <asm/pgtable_64.h>


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

void traversePGD(void)
{
    int i;
    pgd_t* pgds;

    pgds = getvCR3(current->pid);
    pr_info("pgds: %lx\n", pgds);
    for (i = 0;i < 512;i++) {
        unsigned long rangestart = 0xffff000000000000 + ((unsigned long)(i) << 39);
        unsigned long rangeend = rangestart + ((unsigned long)1 << 39);
        pr_info("pgd[%d]: %lx  %lx  [%lx, %lx]\n", i, &pgds[i], pgds[i], rangestart, rangeend);
    }
}

void setINIT_TOP_PGD(void) 
{
    pgd_t* pgds;
    pgd_t* INIT_TOP_PGD;
    // int i;
    INIT_TOP_PGD = 0Xffffffff8260a000;
    pgds = INIT_TOP_PGD;

    pr_info("init_top_pgd: %lx\n", pgds);
    // for (i = 0;i < 512;i++) {
    //     pr_info("pgd[%d]: %lx  %lx\n", i, &pgds[i], pgds[i]);
    // }
    pgds[502].pgd = (unsigned long )(0xbeef);
}


static int __init hello_init(void)
{
    int i;
    // struct task_struct *task;
    // struct mm_struct *mm;
    // unsigned long cr3;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    pgd_t* INIT_TOP_PGD;
    struct mm_struct* INIT_MM;
    // int i;
    INIT_TOP_PGD = 0Xffffffff8260a000;
    INIT_MM = 0xffffffff826f3a60;

    // task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
    // if (task == NULL) 
    //     return 0;
    // mm = task->mm;
    // if (mm == NULL)
    //     mm = task->active_mm;
    // if (mm == NULL)
    //     return 0;
    // cr3 = mm->pgd;
    pr_info("%s init\n", MODULE_NAME);
    // pr_info("cr3: %lx\n", cr3);  
    // checkphymap
    unsigned long addr = 0xffffb88000000000;
    // unsigned long *pos1 = 0xffffffff81000000;
    pgd = pgd_offset(INIT_MM, addr);
    // pgd = pgd_offset_pgd(INIT_TOP_PGD, addr);
    if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
        pr_err("bad pgd\n");
    pr_info("pgd : %lx  %lx, index: %d\n", pgd, pgd->pgd, pgd_index(addr));

    p4d = p4d_offset(pgd, addr);
    pr_info("p4d : %lx  %lx, index: %d\n", p4d, *p4d, p4d_index(addr));
    if (unlikely(p4d_bad(*p4d))) 
        pr_err("bad p4d\n");
    if (p4d_none(*p4d)) {
        pr_info("alloc p4d\n");
        p4d = p4d_alloc(INIT_MM, pgd, addr);
    }

    pr_info("p4d : %lx  %lx, index: %d\n", p4d, *p4d, p4d_index(addr));
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