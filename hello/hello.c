#include <linux/module.h>
#include <linux/mm.h>
#include <linux/init.h>

#define MODULE_NAME "hello"
MODULE_AUTHOR("ppw");
MODULE_LICENSE("GPL v2");

static int __init hello_init(void)
{
    pr_info("%s init\n", MODULE_NAME);
    
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("%s exit\n", MODULE_NAME);
}

module_init(hello_init);
module_exit(hello_exit);