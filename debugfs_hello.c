#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/fs.h>

static struct dentry *hello_dentry;

static int hello_show(struct seq_file *m, void *v)
{
	seq_printf(m, "debugfs hello world\n");

	return 0;
}

static int hello_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_show, inode->i_private);
}

static const struct file_operations hello_fops = {
	.open = hello_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init debugfs_hello_init(void)
{
	hello_dentry = debugfs_create_file("hello", S_IRUGO | S_IWUGO, NULL, NULL, &hello_fops);

	if (!hello_dentry) {
		pr_err("failed to create /sys/kernel/debug/hello\n");
		return -ENOMEM;
	}

	return 0;
}

static void __exit debugfs_hello_exit(void)
{
	debugfs_remove(hello_dentry);
}

module_init(debugfs_hello_init);
module_exit(debugfs_hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chengyihe");
