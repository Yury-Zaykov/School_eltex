#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
 
int len,temp;

char *msg;
 
ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp )
{
    if(count>temp)
    {
        count=temp;
    }
    temp=temp-count;
    copy_to_user(buf,msg, count);
    if(count==0)
        temp=len;
 
    return count;
}
 
ssize_t write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
    copy_from_user(msg,buf,count);
    len=count;
    temp=len;
    return count;
}

struct file_operations proc_fops = {
read:
	read_proc,
write:
	write_proc
};

const struct proc_ops proc_ffops = 
{
proc_read:
	read_proc,
proc_write:
	write_proc
};

void create_new_proc_entry(void)  //use of void for no arguments is compulsory now
{
    proc_create("hello",0,NULL,&proc_ffops);
    msg=kmalloc(10*sizeof(char), GFP_KERNEL);
}
 
int proc_init (void) {
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
    remove_proc_entry("hello",NULL);
    kfree(msg);
}
 
MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);