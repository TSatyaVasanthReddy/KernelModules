#include <linux/types.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};
static LIST_HEAD(birthday_list);
int simple_init(void)
{
	printk(KERN_INFO "Loading myModule\n");
	struct birthday *ptr;
	struct birthday *person;
	int i,yr=1996;
	person=kmalloc(sizeof(*person),GFP_KERNEL);
	person->day=18;
	person->month=6;
	person->year=yr;
	yr++;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);
	for(i=0;i<4;i++)
	{
		person=kmalloc(sizeof(*person),GFP_KERNEL);
		//get_random_bytes(&rand,sizeof(rand));

		person->day=1+(unsigned int)&(person->day)%29;//rand%30;
		//get_random_bytes(&rand,sizeof(rand));
		person->month=1+(unsigned int)&(person->month)%12;//rand%12;
		person->year=yr;
		yr++;
		list_add_tail(&person->list,&birthday_list);
	}
	list_for_each_entry(ptr,&birthday_list,list)
	{
		printk("Student DOB %d/%d/%d\n",ptr->day,ptr->month,ptr->year);
	}
	return 0;
}

void simple_exit(void)
{
	printk(KERN_INFO "Removing myModule\n");
	struct birthday *ptr;
	struct birthday *next;
	list_for_each_entry_safe(ptr,next,&birthday_list,list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk(KERN_INFO "Removed successfully\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked list myModule");
MODULE_AUTHOR("vasanth");
