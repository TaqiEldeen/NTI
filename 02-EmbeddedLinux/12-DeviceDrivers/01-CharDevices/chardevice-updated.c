#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

/************************ MODULE INFO *************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Taqi Eldeen Edrees");
MODULE_DESCRIPTION("A simple module to demonstrate character drivers");


/************************ MACROS *************************/
#define MINOR_NUM   0
#define DEV_COUNT   1
#define MODULE_NAME "my-module"
#define BUFF_SIZE   20

/************************ Global Functions *************************/

/**
 * @brief   Read from the device
 * 
 * @param filp  file pointer
 * @param buff  The user buffer
 * @param count How many bytes to read
 * @param f_pos file position (Want to read from where)
 * @return ssize_t  number of bytes read
 */
ssize_t myDriver_read (struct file * filp, char __user * buff, size_t count, loff_t * f_pos);

/**
 * @brief  Write to the device
 * 
 * @param filp  file pointer
 * @param buff  The user buffer
 * @param count How many bytes to write
 * @param f_pos file position (Want to write from where)
 * @return ssize_t 
 */
ssize_t myDriver_write (struct file * filp, const char __user * buff, size_t count, loff_t * f_pos);
int     myDriver_open   (struct inode *, struct file *);
int     myDriver_close  (struct inode *, struct file *);


/************************ Global Variables *************************/
static dev_t device_number;
static struct cdev my_cdev;
static struct class *device_class;
static struct device *my_device;
static unsigned char G_u8Buffer[BUFF_SIZE] = {0};

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = myDriver_open,
    .release = myDriver_close,
    .read    = myDriver_read,
    .write   = myDriver_write,
};

static int __init major_init(void) {
    int error_code = 0;
    /**
     * 1- Allocate major and minor for the character driver
     * 
     */
    error_code = alloc_chrdev_region(&device_number, MINOR_NUM, DEV_COUNT, MODULE_NAME);
    if(error_code < 0) {
        printk(KERN_ALERT MODULE_NAME": Module Failed to Load: alloc_chrdev_region\n");
        goto ERR_ALLOC_CHAR;
    }

    /**
     * 2- Construct a new cdev init object
     * 
     */
    cdev_init(&my_cdev, &fops);

    /**
     * 3- Add a char device to the system
     * 
     */
    error_code = cdev_add(&my_cdev, device_number, DEV_COUNT);
    if (error_code < 0) {
        printk(KERN_ALERT MODULE_NAME": Module Failed to Load: cdev_add\n");
        goto ERR_CDEV_ADD;
    }
    
    /**
     * 4- generate class file (/sys/class/)
     * 
     */ 
    device_class = class_create(MODULE_NAME);
    if(IS_ERR(device_class)) {
        printk(KERN_ALERT MODULE_NAME": Module Failed to Load: class_create\n");
        error_code = PTR_ERR(device_class);
        goto ERR_CLASS_CREATE;
    }
    
    /**
     * 5- creates a device and registers it with sysfs
     * 
     */
    my_device = device_create(device_class, NULL, device_number, NULL, "my-module-%i", DEV_COUNT);
    if(IS_ERR(my_device)) {
        printk(KERN_ALERT MODULE_NAME": Module Failed to Load: device_create\n");
        error_code = PTR_ERR(my_device);
        goto ERR_DEVICE_CREATE;
    }

    printk(KERN_INFO MODULE_NAME": Module Loaded With Major Number=%d!\n", MAJOR(device_number));    
    return 0;

ERR_DEVICE_CREATE:
    class_destroy(device_class);   
ERR_CLASS_CREATE:
    cdev_del(&my_cdev);
ERR_CDEV_ADD:
    unregister_chrdev_region(device_number, DEV_COUNT);
ERR_ALLOC_CHAR:
    
    return (error_code < 0) ? error_code : -error_code;
}

static void __exit major_exit(void) {
    device_destroy(device_class, device_number);
    class_destroy(device_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(device_number, DEV_COUNT);
    printk(KERN_INFO MODULE_NAME": Module Unloaded !\n");
}

ssize_t myDriver_read (struct file * filp, char __user * buff, size_t count, loff_t * f_pos) {
    int not_copied = 0;

    printk("%s: File position: %lld\n",__func__, *f_pos);
    printk("%s: READING %lld bytes\n",__func__, count);

    if( (count + *f_pos) > BUFF_SIZE) {
        count = BUFF_SIZE - *f_pos;
        printk("%s: adjusted READING to %lld bytes\n",__func__, count);
    }
    
    /* Copy the buffer to the user space */
    not_copied = copy_to_user(buff, &G_u8Buffer[*f_pos], count);
    if(not_copied) {
        printk("ERROR: Failed to copy %d bytes to user space\n", not_copied);
        return -EFAULT;
    }

    /* Update the file position to keep track of the buffer */
    *f_pos += count;
    return count;
}

ssize_t myDriver_write (struct file * filp, const char __user * buff, size_t count, loff_t * f_pos) {
    int not_copied = 0;
    printk("%s: WRITING %lld bytes\n",__func__, count);
    printk("%s: File position: %lld\n",__func__, *f_pos);

    if( (count + *f_pos) > BUFF_SIZE) {
        count = BUFF_SIZE - *f_pos;
    }

    if(count == 0) {
        printk("ERROR: No space left in the buffer\n");
        return -ENOMEM;
    }

    not_copied = copy_from_user(&G_u8Buffer[*f_pos], buff, count);
    if(not_copied) {
        printk("ERROR: Failed to copy %d bytes from user space\n", not_copied);
        return -EFAULT;
    }

    *f_pos += count;
    printk("%s: Written %lld bytes\n",__func__, count);
    printk("%s: File position: %lld\n",__func__, *f_pos);
    return count;
}

int myDriver_open (struct inode *, struct file *) {
    printk(KERN_INFO "Device Opened!\n");
    return 0;
}

int myDriver_close (struct inode *, struct file *) {
    printk(KERN_INFO "Device Closed!\n");
    return 0;
}

module_init(major_init);
module_exit(major_exit);