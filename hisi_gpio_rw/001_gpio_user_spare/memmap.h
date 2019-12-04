/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: memmap.h
*BlogAddr: caibiao-lee.blog.csdn.net
*Description: �ڴ�ӳ��ӿ�ʵ��
*Date:     2019-10-02
*Author:   Caibiao Lee
*Version:  V1.0
*Others:  1.�����ڴ�ӳ��ӿڴ���һ�����������ҪƵ������ĳһ��ַ��
          ���Բ����ͷŸ�ӳ�䣬��ӳ�亯���л�ȥ�����в�ѯ�Ƿ�֮ǰ
          ӳ���˲���û���ͷš�
          2.��HI3520DV400�豸�У��ڴ���С���뵥λ��128�ֽڣ�
          ������һҳ4k
*History:
***********************************************************/

#ifndef __MEM_MAP_H__
#define __MEM_MAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern void * memmap(unsigned int phy_addr, unsigned int size);
extern int memunmap(void * addr_mapped);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 

#endif

