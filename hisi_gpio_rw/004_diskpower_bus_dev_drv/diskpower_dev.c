/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: diskpower_dev.c
*BlogAddr: caibiao-lee.blog.csdn.net
*Description: Ӳ���ϵ��µ��豸ģ��
*Date:     2019-10-02
*Author:   Caibiao Lee
*Version:  V1.0
*Others:   1.���豸ģ�������ں�˼HI3520Xϵ��оƬ
           2.Ӳ�����µ������ΪGPIO_0_2    
*History:
***********************************************************/
#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>

#define DISK_POWER_PIN  2

/* ����/����/ע��һ��platform_device */
static struct resource diskpower_resource[] = {
    [0] = {
        .start = DISK_POWER_PIN,
        .end   = DISK_POWER_PIN,
        .flags = IORESOURCE_MEM,
    },
};

static void diskpower_release(struct device * dev)
{

}

static struct platform_device diskpower_dev = {
    .name    = "diskpower",
    .id      = -1,
    .num_resources  = ARRAY_SIZE(diskpower_resource),
    .resource       = diskpower_resource,
    .dev = { 
    .release = diskpower_release, 
    },
};

static int diskpower_dev_init(void)
{
    platform_device_register(&diskpower_dev);
    return 0;
}

static void diskpower_dev_exit(void)
{
    platform_device_unregister(&diskpower_dev);
}

module_init(diskpower_dev_init);
module_exit(diskpower_dev_exit);

MODULE_AUTHOR("Caibiao Lee");
MODULE_DESCRIPTION("disk power control");
MODULE_LICENSE("GPL");

