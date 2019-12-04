/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: disk_power_drv_readlwritel.c
*BlogAddr: caibiao-lee.blog.csdn.net
*Description: Ӳ���ϵ��µ�����
*Date:     2019-10-02
*Author:   Caibiao Lee
*Version:  V1.0
*Others:   1.�����������ں�˼HI3520Xϵ��оƬ
           2.Ӳ�����µ������ΪGPIO_0_2
           3.ע��IO_ADDRESS��ʹ��
*History:
***********************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <mach/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>

#define DIR_REG_OFFSET             (0x400) /**����Ĵ���ƫ�Ƶ�ַ**/
#define DATA_REG_OFFSET            (0x3fc) /**���ݼĴ���ƫ�Ƶ�ַ**/
#define DISK_POWER_BASE_PHYADDR    IO_ADDRESS(0x12150000) /**GPIO 0 �Ļ���ַ**/
#define DISK_POWER_DATA_PHYADDR    (DISK_POWER_BASE_PHYADDR + DATA_REG_OFFSET) /**GPIO 0 ���ݼĴ�����ַ**/
#define DISK_POWER_DIR_PHYADDR     (DISK_POWER_BASE_PHYADDR + DIR_REG_OFFSET)  /**GPIO 0 ����Ĵ�����ַ**/

static int disk_power_open (struct inode *node, struct file *filp)
{ 
    return 0;
}

static ssize_t disk_power_write (struct file *filp, const char __user *buf, size_t size, loff_t *off)
{
    int pin_num = 0;
    unsigned char val = 0;
    unsigned int old_reg_val = 0;
    unsigned int new_reg_val = 0;
    
    pin_num = 2;

    /**set gpio_0_2 output**/
    old_reg_val = readl((volatile void __iomem *)DISK_POWER_DIR_PHYADDR);
    new_reg_val = (1 << pin_num) |old_reg_val;
    writel(new_reg_val,(volatile void __iomem *)DISK_POWER_DIR_PHYADDR);

    copy_from_user(&val, buf, 1);
    if (val)
    {
        /** power on **/
        old_reg_val = readl((volatile void __iomem *)DISK_POWER_DATA_PHYADDR);
        new_reg_val = (1 << pin_num) |old_reg_val;
        writel(new_reg_val,(volatile void __iomem *)DISK_POWER_DATA_PHYADDR);
        printk("writel: gpio_0_2 0; power on\n");
    }
    else
    {
        /** power off **/
        old_reg_val = readl((volatile void __iomem *)DISK_POWER_DATA_PHYADDR);
        new_reg_val = (~(1 << pin_num)) & old_reg_val;
        writel(new_reg_val,(volatile void __iomem *)DISK_POWER_DATA_PHYADDR);
        printk("writel: gpio_0_2 1; power off\n");
    }

    return 1; 
}

static int disk_power_pin_init(void)
{
    unsigned int old_reg_val = 0;
    unsigned int new_reg_val = 0;
    int pin_num = 2;

    /**set gpio_0_2 output**/
    old_reg_val = readl((volatile void __iomem *)DISK_POWER_DIR_PHYADDR);
    new_reg_val = (1 << pin_num) |old_reg_val;
    writel(new_reg_val,(volatile void __iomem *)DISK_POWER_DIR_PHYADDR);

    /** power on **/
    old_reg_val = readl((volatile void __iomem *)DISK_POWER_DATA_PHYADDR);
    new_reg_val = (1 << pin_num) |old_reg_val;
    writel(new_reg_val,(volatile void __iomem *)DISK_POWER_DATA_PHYADDR);

    printk("init: gpio_0_2 0; power on\n");
}

static int disk_power_release (struct inode *node, struct file *filp)
{
    
    return 0;
}

static struct file_operations diskpower_oprs = {
    .owner = THIS_MODULE,
    .open  = disk_power_open,
    .write = disk_power_write,
    .release = disk_power_release,
};

static struct miscdevice diskpower_ctl = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "disk_power",
    .fops  = &diskpower_oprs,
};

static int __init diskpower_init(void)
{
    int  ret = 0;
    ret = misc_register(&diskpower_ctl);
    if (ret)
    {
        printk(KERN_ERR "register misc gpio fail!\n");
        return ret;
    }

    disk_power_pin_init();
    
    return 0;
}

static void __exit diskpower_exit(void)
{
    misc_deregister(&diskpower_ctl);
}

module_init(diskpower_init);
module_exit(diskpower_exit);

MODULE_AUTHOR("Caibiao Lee");
MODULE_DESCRIPTION("disk power control");
MODULE_LICENSE("GPL");


