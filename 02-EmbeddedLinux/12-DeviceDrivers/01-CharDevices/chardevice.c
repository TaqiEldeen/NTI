#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

struct cdev mycdev ;
dev_t device_number;

char k_buff[100] = {0};
size_t k_buff_len = 100;

static struct class *dev_class;

struct file_operations fops = {
    .read  = readFunction,
    .write = writeFunction
};

/**
 * @brief   This function is called when the device file is read from.
 * 
 * @param filp 
 * @param buff 
 * @param count 
 * @param offp 
 * @return ssize_t 
 */
ssize_t readFunction(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
    size_t bytes_to_copy = count < k_buff_len ? count : k_buff_len;

    if (*offp >= k_buff_len) {
        return 0; // End of file
    }

    if(copy_to_user(buff, k_buff, bytes_to_copy)) {
        return -EFAULT;
    }
    *offp += bytes_to_copy;

    printk(KERN_INFO "Read %ld bytes\n", bytes_to_copy);

    return bytes_to_copy;
}

/**
 * @brief  This function is called when the device file is written to.
 * 
 * @param filp 
 * @param buff 
 * @param count 
 * @param offp 
 * @return ssize_t 
 */
ssize_t writeFunction(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
    size_t bytes_to_copy = count < (k_buff_len - *offp) ? count : (k_buff_len - *offp);
    static long long write_pos = 0;

    printk(KERN_INFO "write pos %ld \n", write_pos);

    if(copy_from_user(k_buff + write_pos, buff, bytes_to_copy)) {
        return -EFAULT;
    }

    *offp += bytes_to_copy;
    write_pos += *offp;
    if(write_pos >= k_buff_len) {
        write_pos = 0;
    }

    printk(KERN_INFO "written %ld bytes\n", bytes_to_copy);

    return bytes_to_copy;
}

/**
 * @brief   This function is called when the module is loaded into the kernel.
 * 
 * @return int 
 */
static int __init charDevice_init(void)
{
    int r_err = 0;

    /*
    * Register the device number dynamically (Major and Minor numbers)
    */
    r_err = alloc_chrdev_region(&device_number, 0, 1, "my_test_device");
    if(r_err < 0) {
        printk("my_module: ERROR\n");
        return 1;
    }

    /**
     * Initialize the cdev structure and add it to the kernel 
     */
    mycdev.owner = THIS_MODULE;
    cdev_init(&mycdev, &fops);
    r_err =  cdev_add(&mycdev, device_number, 1);
    if(r_err < 0) {
        unregister_chrdev_region(device_number, 1);
        printk(KERN_ALERT "Failed to add a char device\n");
        return r_err;
    }

    /**
     * Create a device class (in /sys/class/) and device file (in /dev/)
     * This to make the device accessible from user space
     */
    dev_class = class_create("my_test_device");
    device_create(dev_class, NULL, device_number, NULL, "my_test_device");

    printk(KERN_INFO "Registered successfully with major number %d\n", MAJOR(device_number));
    return 0;
}

/**
 * @brief  This function is called when the module is removed from the kernel.
 * 
 */
static void __exit charDevice_exit(void) {
    class_destroy(dev_class);
    device_destroy(dev_class, device_number);
    cdev_del(&mycdev);
    unregister_chrdev_region(device_number, 1);
}

module_init(charDevice_init);
module_exit(charDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Taqi Eldeen Edrees");
MODULE_DESCRIPTION("A dummy driver");