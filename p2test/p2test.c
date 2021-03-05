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
#include <linux/string.h>

#include <linux/ketag.h>

// #define TB                  (unsigned long)(1) << 40

#define MODULE_NAME "p2test"
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
    cr3 = (unsigned long)mm->pgd;
    return cr3;
}

void traversePGD(void)
{
    int i;
    pgd_t* pgds;

    pgds = (pgd_t*)getvCR3(current->pid);
    pr_info("pgds: %lx\n", (unsigned long)pgds);
    for (i = 0;i < 512;i++) {
        unsigned long rangestart = 0xffff000000000000 + ((unsigned long)(i) << 39);
        unsigned long rangeend = rangestart + ((unsigned long)1 << 39);
        pr_info("pgd[%d]: %lx  %lx  [%lx, %lx]\n", i, (unsigned long)&pgds[i], pgds[i], rangestart, rangeend);
    }
}

void access(unsigned long addr) 
{
    unsigned long *value = (unsigned long*) addr;
    pr_info("access : %lx  %lx\n", addr, (unsigned long)(*value));
}

void checkstruct(unsigned long addr) 
{
    struct task_struct *task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
    struct mm_struct *mm;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    mm = task->mm;
    if (mm == NULL) 
        mm = task->active_mm;
    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
        pr_err("bad pgd\n");
    pr_info("pgd : %lx  %lx, index: %d\n", pgd, pgd->pgd, pgd_index(addr));

    p4d = p4d_offset(pgd, addr);
    if (p4d_none(*p4d) || unlikely(p4d_bad(*p4d)))
        pr_err("bad p4d\n");
    pr_info("p4d : %lx  %lx, index: %d\n", p4d, *p4d, p4d_index(addr));
    if (p4d_present(*p4d)) {
        pr_info("alloc p4d successfully\n");
    } else {
        pr_info("p4d not present\n");
    }

    pud = pud_offset(p4d, addr);
    if (pud_none(*pud) || unlikely(pud_bad(*pud)))
        pr_err("bad pud\n");
    pr_info("pud : %lx  %lx, index: %d\n", pud, *pud, pud_index(addr));
    // pr_info("pud: p4d_page_vaddr: %lx\n", p4d_page_vaddr(*p4d));
    if (pud_present(*pud)) {
        pr_info("alloc pud done\n");
    } else {
        pr_err("pud not present\n");
    }
    
    pmd = pmd_offset(pud, addr);
    // here only check low word on 32bit platform
    if (pmd_none(*pmd))
        pr_err("bad pmd\n");
    pr_info("pmd:  %lx  %lx, index: %d\n", pmd, *pmd, pmd_index(addr));
    if (pmd_present(*pmd)) {
        pr_info("alloc pmd done\n");
    } else {
        pr_err("pmd not present\n");
    }

    pte = pte_offset_kernel(pmd, addr);
    if (pte_none(*pte))
        pr_err("bad pte\n");
    pr_info("pte:  %lx  %lx, index: %d\n", pte, *pte, pte_index(addr));
    if (pte_present(*pte)) {
        pr_info("alloc pte done\n");
    } else {
        pr_err("pte not present\n");
    }
    
}
// unsigned long get_pte_pa(pte_t *pte) 
// {
//     return ((pte->pte)&(0xfffffffff000));
// }
void checkptestruct(unsigned long addr)
{
    struct task_struct *task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
    struct mm_struct *mm;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    mm = task->mm;
    if (mm == NULL) 
        mm = task->active_mm;
    pgd = pgd_offset(mm, addr);

    p4d = p4d_offset(pgd, addr);
    pud = pud_offset(p4d, addr);
    
    pmd = pmd_offset(pud, addr);
    // here only check low word on 32bit platform

    pte = pte_offset_kernel(pmd, addr);
    if (pte_none(*pte))
        pr_err("bad pte\n");
    pr_info("pte:  %lx  %lx, index: %d\n", pte, *pte, pte_index(addr));
    // pr_info("pte to phys:%lx\n", get_pte_pa(pte));
}



static int __init hello_init(void)
{
    int i;   
    unsigned long addr = 0xfffffffffffffff0;
    // unsigned long ketagbase = 0xffffb88000000000;
    unsigned long testaddr = 0xffffb88000000000 + 100*MB + 10 * KB + 100;
    unsigned long *value = (unsigned long*) testaddr;
    unsigned long ptefault =  0xffffb88000001000;
    unsigned long pmdfault =  0xffffb88000200000;
    unsigned long pudfault =  0xffffb88040000000;
    unsigned long pgdfault =  0xffffb90000000000;
    unsigned long ketagtag =  0xffffbf9000000000;
    unsigned long ketagtage=  0xffffc19000000000;
    pr_info("%s init\n", MODULE_NAME); 

    // void (*target)(unsigned long );
    // target = (void *)0xffffffff812a8b09;
    // (*target)(addr);
    // traversePGD();
    // for (i = 0;i < 32;i++)
    //     pr_info("%lx\n", ketag_base + TB*i);
    
    // for (i = 0;i < 4096/8+1;i++) {
    //     pr_info("%lx  :  %lx\n", (unsigned long)&value[i], (unsigned long)value[i]);
    // }
    // alloc_ketag_startpage(ketagbase);
    // checkstruct(ketagbase);
    // ketag_alloc_addr_one(testaddr);
    // ketag_alloc_addr(testaddr, MB);
    // *value = 0x1234567890abcdef;
    ketag_free_addr_one(testaddr);
    checkptestruct(testaddr);
    
    // checkstruct(testaddr);
    // int res = ketag_free_addr_one(testaddr);
    // pr_info("res %d\n", res);
    access(testaddr+KB*9+100);
    // ketag_free_addr_one(testaddr);

    // access(testaddr);
    // access(testaddr+4);
    // unsigned long pa_to_va = 0xffff888042987000;
    // access(pa_to_va);
    // access(testaddr+GB*2);
    
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003