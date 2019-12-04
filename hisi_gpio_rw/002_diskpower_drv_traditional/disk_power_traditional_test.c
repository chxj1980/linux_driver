/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: disk_power_test.c
*BlogAddr: caibiao-lee.blog.csdn.net
*Description: Ӳ���ϵ��µ��������Գ���
*Date:     2019-10-02
*Author:   Caibiao Lee
*Version:  V1.0
*Others:   1.�����������ں�˼HI3520Xϵ��оƬ
           2.Ӳ�����µ������ΪGPIO_0_2 
*History:
***********************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    unsigned char val = 1;
    fd = open("/dev/disk_power", O_RDWR);
    if (fd < 0)
    {
        printf("can't open!\n");
    }
    if (argc != 2)
    {
        printf("Usage :\n");
        printf("%s <on|off>\n", argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "on") == 0)
    {
        val  = 1;
    }
    else
    {
        val = 0;
    }
    
    write(fd, &val, 1);
    
    close(fd);
    
    return 0;
}
