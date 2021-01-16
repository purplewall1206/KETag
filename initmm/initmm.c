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
    // struct mm_struct *mm;

    // pr_info("%s init\n", MODULE_NAME);   
    
    // mm = (struct mm_struct*)0xffffffff826f3a60; 
    // pr_info("initmm   pgd:%lx  %lx\n", mm->pgd, pgd_val(*(mm->pgd)));

    // pr_info("vma %lx\n", mm->mmap);
    // 内核使用vmap stack那么应该一共有4个内核栈地址（2核CPU）
    struct task_struct *task = current;
    pr_info("vmap kernel stack %lx\n", task->stack);
    pr_info("KERNEL_PGD_BOUNDARY:  %d\n", KERNEL_PGD_BOUNDARY);
#ifdef CONFIG_X86_PAE
    // pr_info("PREALLOCATED_PMDS : %d\n", PREALLOCATED_PMDS);
    pr_info("define config_x86_pae\n");
#else
    pr_info("PREALLOCATED_PMDS = 0\n");
#endif
    return 0;
}

static void __exit hello_exit(void)
{
    // pr_info("%s exit\n", MODULE_NAME);
}


// static void pgd_prepopulate_pmd(struct mm_struct *mm, pgd_t *pgd, pmd_t *pmds[])
// {
// 	p4d_t *p4d;
// 	pud_t *pud;
// 	int i;

// 	if (PREALLOCATED_PMDS == 0) /* Work around gcc-3.4.x bug */
// 		return;

// 	p4d = p4d_offset(pgd, 0);
// 	pud = pud_offset(p4d, 0);

// 	for (i = 0; i < PREALLOCATED_PMDS; i++, pud++) {
// 		pmd_t *pmd = pmds[i];

// 		if (i >= KERNEL_PGD_BOUNDARY)
// 			memcpy(pmd, (pmd_t *)pgd_page_vaddr(swapper_pg_dir[i]),
// 			       sizeof(pmd_t) * PTRS_PER_PMD);

// 		pud_populate(mm, pud, pmd);
// 	}
// }


module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003