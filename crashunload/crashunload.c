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
#include <linux/kallsyms.h>
#include <linux/string.h>

#include <linux/ketag.h>

#define MODULE_NAME "crashunload"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

char crashname[] = "p2test";

static int __init crashunload_init(void)
{
    struct list_head *modules;
    struct module *mod = 0;
    struct module *list_mod;
    unsigned long addr = 0xffffb88000000001;
    // char *sym_name;
    // unsigned long sym_addr;
    pr_info("%s init\n", MODULE_NAME);    
    // alloc_ketag_startpage(addr);
    // *sym_name = "modules";
    // sym_addr = kallsyms_lookup_name(sym_name);
    modules = (struct list_head*) get_sym_modules();
    pr_info("modules address : %016lx\n", (unsigned long) modules);

    list_for_each_entry(list_mod, modules, list) {
        if (strcmp(list_mod->name, crashname) == 0)
            mod = list_mod;
    }
    if (mod == 0) {
        pr_debug("p2test not found\n");
        return -1;
    }
    mod->state = MODULE_STATE_LIVE;

    uint64_t refcnt = atomic_read(&(mod->refcnt)); 
    atomic_set(&(mod->refcnt), 1); 
    return 0;
}

static void __exit crashunload_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(crashunload_init);
module_exit(crashunload_exit);

// 79b7c000   79b7c003