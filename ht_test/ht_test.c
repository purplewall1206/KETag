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
#include <linux/hashtable.h>
#include <asm/tsc.h>

#include <linux/ketag.h>

#define MODULE_NAME "ht_test"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

struct ketag_pte_object
{
    unsigned long index;
    bool present;

    struct hlist_node node;
};

static int __init ht_test_init(void)
{
    unsigned int key;
    struct ketag_pte_object* obj;
    cycles_t start;
    cycles_t end;
    DEFINE_HASHTABLE(htable, 8);
    pr_info("%s init\n", MODULE_NAME);    
    struct ketag_pte_object obj0 = {
        .index = 0,
        // .present = true;
    };
    hash_add(htable, &obj0.node, obj0.index);

    struct ketag_pte_object obj1 = {
        .index = 1,
        // .present = true;
    };
    hash_add(htable, &obj1.node, obj1.index);

    struct ketag_pte_object obj2 = {
        .index = 0xffff134324,
        // .present = true;
    };
    hash_add(htable, &obj2.node, obj2.index);

    struct ketag_pte_object obj3 = {
        .index = 0xffffffff81000000,
        // .present = true;
    };
    if (hash_hashed(&obj3.node)) {
        pr_info("obj3 hashed\n");
    }  else {
        pr_info("obj3 not hashed\n");
    }

    if (hash_hashed(&obj1.node)) {
        pr_info("obj1 hashed\n");
    }  else {
        pr_info("obj1 not hashed\n");
    }

    // find
    key = 1;
    start = get_cycles();
    hash_for_each_possible(htable, obj, node, key) {
        if (obj->index == key) {
            pr_info("find key %u\n", key);
        }
    }
    end = get_cycles();
    pr_info("end - start : %llu cycles\n", end - start);

    start = get_cycles();
    if (ketag_is_pte_present((unsigned long )0xffffffff81000000))
        pr_info("find pte %lx\n", (unsigned long )0xffffffff81000000);
    end = get_cycles();
    pr_info("end - start : %llu cycles\n", end - start);
    return 0;
}

static void __exit ht_test_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(ht_test_init);
module_exit(ht_test_exit);

// 79b7c000   79b7c003