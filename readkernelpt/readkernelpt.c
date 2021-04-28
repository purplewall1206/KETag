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


#define MODULE_NAME "readkernelpt"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

struct mm_struct *INIT_MM = (struct mm_struct*)0xffffffff829c6ea0;
// ffffffff82810000 D init_top_pgt

bool access(unsigned long addr) {
    pgd_t* pgd;
    p4d_t* p4d;
    pud_t* pud;
    pmd_t* pmd;
    pte_t* pte;
    // int i;
    struct mm_struct *mm;
    mm = (struct mm_struct*)0xffffffff829c6ea0;
    pgd = pgd_offset(mm, addr);
    if (!pgd_present(*pgd) || pgd_none(*pgd) || unlikely(pgd_bad(*pgd))) {
        pr_err("pgd not present\n");
        return false;
    }
    p4d = p4d_offset(pgd, addr);
    if (!p4d_present(*p4d) || p4d_none(*p4d) || unlikely(p4d_bad(*p4d))) {
        pr_err("p4d not present\n");
    }
    pud = pud_offset(p4d, addr);
    if (!pud_present(*pud) || pud_none(*pud) || unlikely(pud_bad(*pud))) {
        if (pud_none(*pud) || unlikely(pud_bad(*pud))) {
            pr_err("pud none\n");
        }
        pr_err("pud not present\n");
        return false;
    }
    pmd = pmd_offset(pud, addr);
    if (!pmd_present(*pmd) || pmd_none(*pmd)) {
        pr_err("pmd not present\n");
        return false;
    }
    pte = pte_offset_kernel(pmd, addr);
    if (!pte_present(*pte) || pte_none(*pte)) {
        pr_err("pte not present\n");
        if (pte_none(*pte)) {
            pr_err("pte none\n");
            return false;
        }
            
        
    }
    unsigned long *val = (unsigned long *) addr;
    pr_info("access: %016lx  %016lx\n", addr, *val);
    return true;
}

static int __init readkernelpt_init(void)
{
    unsigned long startup_64;
    unsigned long dirmap ;
    unsigned long dirend;
    pgd_t* pgd;
    pgd_t* dirpgd;
    p4d_t* p4d;
    pud_t* pud;
    pmd_t* pmd;
    pte_t* pte;
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    struct mm_struct *mm;
    unsigned long addr;
    unsigned long pudaddr;
    unsigned long pmdaddr;
    unsigned long caladdr;
    mm = (struct mm_struct*)0xffffffff829c6ea0;
    startup_64 = 0xffffffff81000000;
    dirmap = 0xffff888000000000;
    dirend = 0xffffc88000000000;
    
    // if (!access(dirmap + 1*GB)) {
    //     pr_err("not present\n");
    // }

    pgd = mm->pgd;
    // addr = 0xffff000000000000;
    // for (i = 0;i < 512;i++) {
    //     addr = 0xffff000000000000 + ((unsigned long)i << 39);
    //     if (pgd[i].pgd == 0) continue;
    //     if (addr >= ketag_base && addr <= ketag_end) continue;
    //     pr_info("pgd[%3d]: %016lx  [%016lx, %016lx)\n", i,  pgd[i].pgd, addr, addr + 512*GB);
    // }

    dirpgd = &pgd[273];
    addr = 0xffff000000000000 + ((unsigned long)273 << 39);
    pud = (pud_t*) 0xffff888003402000;
    for (i = 0;i < 12;i++) {
        pudaddr = addr + ((unsigned long )i << 30);
        pr_info("pud[%3d]: %016lx  [%016lx, %016lx)\n", i, pud[i].pud, pudaddr, pudaddr + GB);
    }
    addr = dirmap - 4*KB;
    for (i = 0; addr < dirmap + 9 * GB;i++) {
        addr += 4*KB;
        pgd = pgd_offset(mm, addr);
        if (!pgd_present(*pgd) || pgd_none(*pgd) || unlikely(pgd_bad(*pgd))) {
            // pr_err("pgd not present\n");
            // return false;
            continue;
        }
        n = i;
        p4d = p4d_offset(pgd, addr);
        if (!p4d_present(*p4d) || p4d_none(*p4d) || unlikely(p4d_bad(*p4d))) {
            // pr_err("p4d not present\n");
            continue;
        }
        m = i;
        pud = pud_offset(p4d, addr);
        if (!pud_present(*pud) || pud_none(*pud) || unlikely(pud_bad(*pud))) {
            if (pud_none(*pud) || unlikely(pud_bad(*pud))) {
                // pr_err("pud none\n");
            }
            // pr_err("pud not present\n");
            // return false;
            continue;
        }
        l = i;
        pmd = pmd_offset(pud, addr);
        if (!pmd_present(*pmd) || pmd_none(*pmd)) {
            // pr_err("pmd not present\n");
            // return false;
            continue;
        }
        k = i;
        pte = pte_offset_kernel(pmd, addr);
        if (!pte_present(*pte) || pte_none(*pte)) {
            // pr_err("pte not present\n");
            if (pte_none(*pte)) {
                // pr_err("pte none\n");
                // return false;
                continue;
            }
        }
        // pr_info("access %d: %016lx\n", i, addr);
        j = i;
    }
    pr_info("max 4k pages: %d\n", j);
    pr_info("max 2M pages: %d\n", k);
    pr_info("max 1G pages: %d\n", l);
    pr_info("%d  %d\n", m, n);
    return 0;
}

static void __exit readkernelpt_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(readkernelpt_init);
module_exit(readkernelpt_exit);

// 79b7c000   79b7c003