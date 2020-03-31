#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* Module entry point */
int hw2_linear_init(void) {
    printk(KERN_INFO "Loading Module\n");
    /* Traverse linearly*/
    struct task_struct *task_list;
    for_each_process(task_list){
        printk("pid: %d | pname: %s | state: %ld \n",task_list->pid,task_list->comm,task_list->state);
    }
    printk(KERN_INFO "Success!\n");
    return 0;
}

/* Module exist point */
void hw2_linear_exit(void){
     printk(KERN_INFO "Remove Module\n");
} 

/* Register module entry/exit pts */

module_init(hw2_linear_init);
module_exit(hw2_linear_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HW2_LINEAR Module");
MODULE_AUTHOR("justinyeh1995");                                                                            