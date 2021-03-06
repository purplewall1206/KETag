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


#define MODULE_NAME "lkm_readpt"
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
    int i;
    unsigned long cr30 = pid_to_cr3(current->pid);
    
    // pgd_t *pgd = __va(cr30);
    pr_info("%d : %lx   %lx    %lx \n", current->pid, cr30, __va(cr30));
    pgd_t* pgds = (pgd_t*) kmalloc(4096, GFP_KERNEL);
    pgds = __va(cr30);
    
    for (i = 0;i < 512;i++) {
        if (pgds[i].pgd != 0)
            pr_info("pgd[%d]: %lx, %lx\n", i, &pgds[i], pgds[i]);
    }
}

void get_pte(void)
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
    
    unsigned long addr = 0xffffffff81000010;
    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
        pr_err("bad pgd\n");
    pr_info("pgd : %lx  %lx, index: %d\n", pgd, pgd->pgd, pgd_index(addr));

    p4d = p4d_offset(pgd, addr);
    if (p4d_none(*p4d) || unlikely(p4d_bad(*p4d)))
        pr_err("bad p4d\n");
    pr_info("p4d : %lx  %lx, index: %d\n", p4d, *p4d, p4d_index(addr));

    pud = pud_offset(p4d, addr);
    if (pud_none(*pud) || unlikely(pud_bad(*pud)))
        pr_err("bad pud\n");
    pr_info("pud : %lx  %lx, index: %d\n", pud, *pud, pud_index(addr));
    // pr_info("pud: p4d_page_vaddr: %lx\n", p4d_page_vaddr(*p4d));
    
    pmd = pmd_offset(pud, addr);
    // here only check low word on 32bit platform
    if (pmd_none(*pmd))
        pr_err("bad pmd\n");
    pr_info("pmd:  %lx  %lx, index: %d\n", pmd, *pmd, pmd_index(addr));
    if (pmd_large(*pmd)) {
        pr_info("pmd: 2MB page\n");
        struct page *p = pmd_page(*pmd);
        unsigned long pageaddr = page_address(p);
        pr_info("page address : %lx\n", pageaddr);
        int i;
        char *list = (char*)addr;

        // in page offset 21bits
        unsigned long offset = addr & ((1 << 21)-1);

        char* list1 = (char*)(pageaddr+offset);
        for (i = 0;i < 100;i++) {
            printk("%lx->%lx,   %lx->%lx  %d\n", &list[i], list[i], &list1[i], list1[i], (list[i] == list1[i]));
        }
        printk("\n");
    } else {
        pte = pte_offset_kernel(pmd, addr);
        struct page* p = pte_page(*pte);
        unsigned long pageaddr = page_address(p);

        // in page offset 12bits
        unsigned long offset = addr & ((1 << 12) -1);
        pr_info("page address: %lx, %lx\n", pageaddr, pageaddr + offset);
    }

    

}

int (*dump_pt)(unsigned long addr);
static int __init hello_init(void)
{
    pr_info("%s init\n", MODULE_NAME);
    unsigned long CR0 = read_cr0();
    unsigned long CR3 = __read_cr3();
    unsigned long CR4 = __read_cr4();
    pr_info("CR0 : %lx   %lx   %lx\n", CR0, read_cr3_pa(), __va(read_cr3_pa()));
    pr_info("CR3 : %lx\n", CR3);
    pr_info("CR4 : %lx\n", CR4);
    get_CR3();
    get_pte();
    unsigned long addr = 0xffffffff81000010;

    // 这里内核在处理page fault时提供了一个函数，和我实现的功能基本一致，因此这里搞个函数指针直接调用
    dump_pt = 0xffffffff81082420;
    dump_pt(addr);
    
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003