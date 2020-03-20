#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


/*Hw1 Data Structure*/
typedef struct node_student {
    int id;
    int year;
    int month;
    int day;
    struct list_head node_link;
}node_student;

struct node_student* create_student(int id, int y, int m, int d) {
    struct node_student *student ;  
    student = kmalloc(sizeof(struct node_student), GFP_KERNEL);
    student->id = id;
    student->year = y;
    student->month = m;
    student->day = d;
    return student;
}
//Head of the list
LIST_HEAD(student_list);
// struct list_head student_list;
// INIT_LIST_HEAD(&student_list);

/* Module entry point */
int hw1_init(void) {
    printk(KERN_INFO "Loading Module\n");
    /*Construct students list */
    node_student* student1 = create_student(106062540,1976,7,15);
    list_add_tail(&student1->node_link, &student_list);
    node_student* student2 = create_student(106062899,1973,3,18);
    list_add_tail(&student2->node_link, &student_list);
    node_student* student3 = create_student(106062569,1950,2,16);
    list_add_tail(&student3->node_link, &student_list);
    node_student* student4 = create_student(106061359,1945,7,11);
    list_add_tail(&student4->node_link, &student_list);
    node_student* student5 = create_student(106054893,1911,1,10);
    list_add_tail(&student5->node_link, &student_list);
    /*Traverse the list*/
    printk(KERN_INFO "Traverse the student list\n");
    node_student* stu;
    list_for_each_entry(stu, &student_list, node_link) {
        printk("%d, %d-%d-%d.\n",stu->id,stu->year,stu->month,stu->day);
    };
    printk(KERN_INFO "Success!\n");
    return 0;
}

/* Module exist point */
void hw1_exit(void) {
    node_student *stu, *tmp;
    printk(KERN_INFO "Remove Module\n");
    list_for_each_entry_safe(stu, tmp, &student_list, node_link) {
        list_del(&stu->node_link);
        kfree(stu);
    }
}

/* Register module entry/exit pts */

module_init(hw1_init);
module_exit(hw1_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HW1 Module");
MODULE_AUTHOR("justinyeh1995");