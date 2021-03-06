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

// #include <linux/ketag.h>
// 
// #define TB                  (unsigned long)(1) << 40

#define MODULE_NAME "p2test"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");
// unsigned long getvCR3(int pid) 
// {
//     struct task_struct *task;
//     struct mm_struct *mm;
//     unsigned long cr3;

//     task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
//     if (task == NULL) 
//         return 0;
//     mm = task->mm;
//     if (mm == NULL)
//         mm = task->active_mm;
//     if (mm == NULL)
//         return 0;
//     cr3 = (unsigned long)mm->pgd;
//     return cr3;
// }

// void traversePGD(void)
// {
//     int i;
//     pgd_t* pgds;

//     pgds = (pgd_t*)getvCR3(current->pid);
//     pr_info("pgds: %lx\n", (unsigned long)pgds);
//     for (i = 0;i < 512;i++) {
//         unsigned long rangestart = 0xffff000000000000 + ((unsigned long)(i) << 39);
//         unsigned long rangeend = rangestart + ((unsigned long)1 << 39);
//         pr_info("pgd[%d]: %lx  %lx  [%lx, %lx]\n", i, (unsigned long)&pgds[i], (pgds[i]), rangestart, rangeend);
//     }
// }

// void access(unsigned long addr) 
// {
//     unsigned long *value = (unsigned long*) addr;
//     pr_info("access : %lx  %lx\n", addr, (unsigned long)(*value));
// }

// void checkstruct(unsigned long addr) 
// {
//     struct task_struct *task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
//     struct mm_struct *mm;
//     pgd_t *pgd;
//     p4d_t *p4d;
//     pud_t *pud;
//     pmd_t *pmd;
//     pte_t *pte;
//     mm = task->mm;
//     if (mm == NULL) 
//         mm = task->active_mm;
//     pgd = pgd_offset(mm, addr);
//     if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
//         pr_err("bad pgd\n");
//     pr_info("pgd : %lx  %lx, index: %d\n", (unsigned long)pgd, (pgd->pgd), pgd_index(addr));

//     p4d = p4d_offset(pgd, addr);
//     if (p4d_none(*p4d) || unlikely(p4d_bad(*p4d)))
//         pr_err("bad p4d\n");
//     pr_info("p4d : %lx  %lx, index: %d\n", (unsigned long)p4d, (*p4d), p4d_index(addr));
//     if (p4d_present(*p4d)) {
//         pr_info("alloc p4d successfully\n");
//     } else {
//         pr_info("p4d not present\n");
//     }

//     pud = pud_offset(p4d, addr);
//     if (pud_none(*pud) || unlikely(pud_bad(*pud)))
//         pr_err("bad pud\n");
//     pr_info("pud : %lx  %lx, index: %d\n", (unsigned long)pud, (*pud), pud_index(addr));
//     // pr_info("pud: p4d_page_vaddr: %lx\n", p4d_page_vaddr(*p4d));
//     if (pud_present(*pud)) {
//         pr_info("alloc pud done\n");
//     } else {
//         pr_err("pud not present\n");
//     }
    
//     pmd = pmd_offset(pud, addr);
//     // here only check low word on 32bit platform
//     if (pmd_none(*pmd))
//         pr_err("bad pmd\n");
//     pr_info("pmd:  %lx  %lx, index: %d\n", (unsigned long)pmd, (*pmd), pmd_index(addr));
//     if (pmd_present(*pmd)) {
//         pr_info("alloc pmd done\n");
//     } else {
//         pr_err("pmd not present\n");
//         return;
//     }

//     pte = pte_offset_kernel(pmd, addr);
//     if (pte_none(*pte))
//         pr_err("bad pte\n");
//     pr_info("pte:  %lx  %lx, index: %d\n", (unsigned long)pte, (*pte), pte_index(addr));
//     if (pte_present(*pte)) {
//         pr_info("alloc pte done\n");
//     } else {
//         pr_err("pte not present\n");
//     }
    
// }
// // unsigned long get_pte_pa(pte_t *pte) 
// // {
// //     return ((pte->pte)&(0xfffffffff000));
// // }
// void checkptestruct(unsigned long addr)
// {
//     struct task_struct *task = pid_task(find_vpid(current->pid), PIDTYPE_PID);
//     struct mm_struct *mm;
//     pgd_t *pgd;
//     p4d_t *p4d;
//     pud_t *pud;
//     pmd_t *pmd;
//     pte_t *pte;
//     mm = task->mm;
//     if (mm == NULL) 
//         mm = task->active_mm;
//     pgd = pgd_offset(mm, addr);

//     p4d = p4d_offset(pgd, addr);
//     pud = pud_offset(p4d, addr);
    
//     pmd = pmd_offset(pud, addr);
//     // here only check low word on 32bit platform

//     pte = pte_offset_kernel(pmd, addr);
//     if (pte_none(*pte))
//         pr_err("bad pte\n");
//     pr_info("pte:  %lx  %lx, index: %lu\n", (unsigned long)pte, (*pte), pte_index(addr));
//     // pr_info("pte to phys:%lx\n", get_pte_pa(pte));
// }



static int __init hello_init(void)
{
    // int i;   
    // unsigned long addr = 0xfffffffffffffff0;
    // unsigned long ketagbase = 0xffffb88000000000;
    // unsigned long ketag_stack;
    // unsigned long testaddr = 0xffffb88000000000 + 100*MB + 10 * KB + 100;
    // unsigned long len = 1000;
    // unsigned long *value = (unsigned long*) testaddr;
    // unsigned long ptefault =  0xffffb88000001000;
    // unsigned long pmdfault =  0xffffb88000200000;
    // unsigned long pudfault =  0xffffb88040000000;
    // unsigned long pgdfault =  0xffffb90000000000;
    // unsigned long ketagtag =  0xffffbf9000000000;
    // unsigned long ketagtage=  0xffffc19000000000;
    pr_info("%s init  GFP_KERNEL %u\n", MODULE_NAME, GFP_KERNEL); 

    // unsigned long overflow = 0xffffffffffffffff;
    // pr_info("%d\n", overflow);
    // overflow = overflow++;
    // pr_info("%d\n", overflow/0);

    // void* ret = ketag_kmalloc(len, GFP_KERNEL, (char)0b11000011);
    // void* ret = __kmalloc(sizeof(char)*512, GFP_KERNEL);
    void* ret = kmalloc(sizeof(char)*512, GFP_KERNEL);
    int x = 100;
    ret = kmalloc(x, GFP_KERNEL);
    // void* ret = (void*) 0xffff888200433a00;
    // unsigned long tagaddr = ketag_addr_cal((unsigned long)ret);
    // if (!ketag_is_pte_present(tagaddr)) {
    //     ketag_alloc_addr(tagaddr, 64);
    //     pr_info("not present\n");
    // } else {
    //     pr_info("presented \n");
    // }
    // ketag_set_value(tagaddr, 64, (char)0b11001111);

    // pr_info("p2test-- ketag_kmalloc : %016lx  %016lx   %u\n", (unsigned long)ret, tagaddr,100 );
    // checkptestruct(tagaddr);

    // access(ketag_addr_cal((unsigned long)0xffffffff81000000));
    // access(ketag_addr_cal((unsigned long)0xffffffff81000000)+KB);
    // access(ketag_addr_cal((unsigned long)0xffffffff81000000)+ KB*2);

    // access(tagaddr);
    // access(tagaddr+10);
    // access(tagaddr+16);
    // ketag_kfree(ret);
    // checkptestruct(tagaddr);
    // access(tagaddr);
    // access(tagaddr+10);
    // access(tagaddr+16);

    // ret = kmalloc(len, GFP_KERNEL);
    // tagaddr = ketag_addr_cal((unsigned long)ret);
    // pr_info("p2test-- kmalloc : %016lx  %016lx   %u\n", (unsigned long)ret, tagaddr,100 );
    // checkptestruct(tagaddr);
    // access(tagaddr);
    // access(tagaddr+10);
    // access(tagaddr+16);
    // kfree(ret);
    // checkptestruct(tagaddr);
    // access(tagaddr);
    // access(tagaddr+10);
    // access(tagaddr+16);

    // ketag_stack = ketag_addr_cal((unsigned long) current->stack);
    // pr_info("ketag_stack: tag:%016lx\n", ketag_stack);
    // ketag_set_stack(ketag_addr_cal((unsigned long) current->stack));
    // checkstruct(ketag_stack); 
    // access(ketag_stack);

    // access(ketag_addr_cal((unsigned long) 0xffffffff81000000));
    // access(ketag_addr_cal((unsigned long) 0xffffffff81000000) + 10);
    // access(ketag_addr_cal((unsigned long) 0xffffffff82600000));
    // access(ketag_addr_cal((unsigned long) 0xffffffff82600000) + 100);

    // ketag_set_stack(ketag_addr_cal((unsigned long) current->stack));
    // // ketag_stack_entry(0b11111111);
    // access(ketag_addr_cal((unsigned long) current->stack));
    // ketag_stack_entry(0b11111111);
    // access(ketag_addr_cal(ketag_get_rbp()));
    // ketag_stack_exit();
    // access(ketag_addr_cal(ketag_get_rbp()));
    // unsigned long rbp = 0x0;
    // asm("movq %%rbp, %0\n\t":"=r"(rbp));
    // pr_info("get rbp \n%016lx\n%016lx\n%d\n", rbp, ketag_get_rbp(), (rbp == ketag_get_rbp()));
// #define ketag_stack_entry(x)  ketag_set_value(ketag_addr_cal(keteg_get_rbp()), 2, x)
// #define ketag_stack_exit(x)   ketag_set_value(ketag_addr_cal(ketag_get_rbp()), 2, 0b00000000)
   
    // pr_info("%016lx\n", *(unsigned long*)tagaddr);
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
    // ketag_free_addr(testaddr, MB);
    // *value = 0x1234567890abcdef;
    // ketag_free_addr_one(testaddr);

    
    // checkstruct(testaddr);
    // int res = ketag_free_addr_one(testaddr);
    // pr_info("res %d\n", res);
    // access(testaddr+KB*9+100);
    // ketag_free_addr_one(testaddr);

    // access(testaddr);
    // access(testaddr+4);
    // unsigned long pa_to_va = 0xffff888042987000;
    // access(pa_to_va);
    // access(testaddr+GB*2);

    // __ketag_entry_gate__((char)0b10010110);
    // pr_info("%016lx  %016lx\n", (unsigned long)current->stack, 
    //             ketag_addr_cal((unsigned long) current->stack) );
    // access(ketag_addr_cal(ketag_get_rbp()));
    // pr_info("ketag check %d\n",ketag_check(ketag_get_rbp(), (char) 0b10010110) );
    // if (!ketag_check(ketag_get_rbp(), (char) 0b10010110)   ) {
    //     pr_info("cannot access\n");
    // } else {
    //     pr_info("we can access\n");
    // }
    
    // ketag_stack_exit();
    // access(ketag_addr_cal(ketag_get_rbp()));
    // if (!ketag_check(ketag_get_rbp(), (char) 0b10010110)   ) {
    //     pr_info("cannot access\n");
    // } else {
    //     pr_info("we can access\n");
    // }
    // __ketag_exit_gate__;
    // checkptestruct(ketag_addr_cal((unsigned long) current->stack));
    // access(ketag_addr_cal(ketag_get_rbp()));

    // pr_info("ketag check %d\n",ketag_check(ketag_get_rbp(), (char) 0b10010110) );

    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);

// 79b7c000   79b7c003