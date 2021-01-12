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


#define MODULE_NAME "hello"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");



unsigned long pid_to_cr3(int pid) 
{
    struct task_struct *task;
    struct mm_struct *mm;
    void *cr3_virt;
    unsigned long cr3_phys;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL)
        return 0;
    
    mm = task->mm;
    if (mm == NULL) {
        mm = task->active_mm;
    }
    if (mm == NULL)
        return 0;
    cr3_virt = (void*) mm->pgd;
    cr3_phys = virt_to_phys(cr3_virt);
    return cr3_phys;
}

void get_CR3(void) 
{
    unsigned long cr30 = pid_to_cr3(current->pid);
    unsigned long cr31 = __read_cr3();
    pgd_t *pgd = __va(cr30);
    pr_info("%d : %lx   %lx    %lx   %lx\n", current->pid, cr30, cr31, __va(cr30), pgd->pgd);
    
}

void get_pte(void)
{
    struct task_struct *task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
    struct mm_struct *mm;
    mm = task->mm;
    if (mm == NULL) 
        mm = task->active_mm;
    
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *ptep;
    unsigned long addr = 0xffffffffad000000;
    pgd = pgd_offset(mm, addr);
    pr_info("pgd : %lx\n", pgd);
    if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
        pr_err("bad pgd\n");
}

static int __init hello_init(void)
{
    pr_info("%s init\n", MODULE_NAME);
    get_CR3();
    // kern_pgtable();
    get_pte();
    
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003