#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
/*Each task_struct(process descripter) 
has a pointer to the task_struct parent 
and a "list" of children*/
/* Don't use struct task_struct *current, it is a global variable in task_struct*/
void dfs(struct task_struct *curr){
    /*current task_struct*/
    printk("pid: %d | pname: %s | state: %ld \n",curr->pid,curr->comm,curr->state); 
    
    struct task_struct *child;
    struct list_head *list_cursor; 
    /*traverse all children*/
    list_for_each(list_cursor, &curr->children) {
        child = list_entry(list_cursor, struct task_struct, sibling);
        dfs(child);
    }       
}


/* Module entry point */
int hw2_dfs_init(void) {
    printk(KERN_INFO "Load Module\n");
    printk(KERN_INFO "DFS Starting...\n");
    /* Traverse dfs tree*/
    //struct task_struct *task_list = &init_task;
    dfs(&init_task);    
    printk(KERN_INFO "DFS Finished!\n");
    return 0;
}

/* Module exist point */
void hw2_dfs_exit(void){
     printk(KERN_INFO "Remove Module\n");
} 

/* Register module entry/exit pts */

module_init(hw2_dfs_init);
module_exit(hw2_dfs_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HW2_DFS Module");
MODULE_AUTHOR("justinyeh1995");                                                            