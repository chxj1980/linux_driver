/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: GPT_DiskPart.h
*BlogAddr: caibiao-lee.blog.csdn.net
*Description:���̷�����ͷ�ļ�
*Date:     2019-10-12
*Author:   Caibiao Lee
*Version:  V1.0
*Others:
*History:
***********************************************************/
#ifndef __DISKPART_H__
#define __DISKPART_H__

#include "GPT_struct.h"

#define GPTP_LOG   printf

#pragma pack(1)

#define SECTOR_BYTE_NUM         (512)    /*ÿ�������Ĵ�С*/
#define SECTORS_PER_TRACK       (63)     /*ÿ��������*/
#define DISK_HEAD_NUM           (255)    /*��ͷ��*/
#define GPT_MAX_PART_NUM        (128)    /*GPT֧�ֵ�����������*/
#define GPT_PART_ITEMS          (128)    /*GPTÿ������������ռ���ֽ���*/
#define MBR_SECTONUM            (1)      /*MBRռ�õ�������*/
#define GPT_HEAD_SECTONUM       (1)      /*GPT��ͷռ�õ�������*/
#define GPT_TABLE_SECTONUM      (32)     /*GPT����ռ�õ�������*/         
#define MBR_START_SECNO         (0)      /*MBR������������*/
#define GPT_HEAD_SECNO          (MBR_START_SECNO + MBR_SECTONUM)   /*GPT������ͷ��������*/
#define GPT_TABLE_SECNO         (GPT_HEAD_SECNO + GPT_HEAD_SECTONUM)  /*GPT ������Ŀ�ʼ������*/
#define GPT_DATA_START_SECNO    (GPT_TABLE_SECNO + GPT_TABLE_SECTONUM)   /*GPT��������ʼ��������*/
#define  GPT_HEAD_BACKUP_SECNO(DiskTotalSec)              (DiskTotalSec - GPT_HEAD_SECTONUM)/*GPT��ͷ���ݿ�ʼ�������ŴӴ��̺�������*/
#define  GPT_TABLE_BACKUP_SECNO(DiskTotalSec)             (GPT_HEAD_BACKUP_SECNO(DiskTotalSec) - GPT_TABLE_SECTONUM)/*GPT������ı��ݵĿ�ʼ������*/
#define  GPT_DATA_END_SECNO(DiskTotalSec)                 (GPT_TABLE_BACKUP_SECNO(DiskTotalSec) - 1)

/***********************************************************/
/*******************error num define************************/
/***********************************************************/
#define WRITE_GOP_ERRNO           -0x00 
#define WRITE_NODE_ERRNO          -0x01 
#define WRITE_STORE_ERRNO         -0x03 
#define WRITE_VLINK_ERRNO         -0x04 
#define PARA_ERROR                -0x05 
#define MALLOC_ERROR              -0x06 
#define AVLINK_NULL_ERROR         -0x07 
#define GET_AVLINK_NODE_ERROR     -0x08 
#define CREATE_CLASS_ERROR        -0x09 
#define FILE_NO_ERROR             -0x0A 
#define FILE_OP_ERROR             -0x0B 
#define LOCK_ERROR                -0x0C 
#define UNLOCK_ERROR              -0x0D 
#define LSEEK_ERROR               -0x0E 
#define READ_ERROR                -0x0F 
#define WRITE_ERROR               -0x10 
#define NODE_INDEX_ERROR          -0x11 
#define NODE_NAME_ERROR           -0x12 
#define TYPE_ERROR                -0x13 
#define FTPFILE_ERROR             -0x14 
#define CREATE_THREAD_ERROR       -0x15 
#define UNMOUNT_ERROR             -0x16 
#define PART_ERROR                -0x17 
#define GET_COVER_ERROR           -0x18 
#define FSYNC_ERROR               -0x19 
#define IOCTL_ERROR               -0x1A 
#define STR_LEN_ERROR             -0x1B 
#define FREE_CLUS_ERROR           -0x1D 
#define FAT_EXTERN_ERROR          -0x1E 
#define PART_INDEX_ERROR          -0x1F 
#define DISK_SIZE_ERROR           -0x20 
#define DISK_FLAGE_ERROR          -0x21 
#define PART_TYPE_ERROR           -0x22 
#define PART_AVLINK_SORT_ERROR    -0x23 
#define PART_AVLINK_END_ERROR     -0x24 
#define PART_AVLINK_WRITE_ERROR   -0x25 
#define PART_AVNODE_ERROR         -0x25 
#define SELECT_ERROR              -0x26 
#define DISK_TRACK_BAD            -0x27 

#pragma pack()

class GPTDiskPart
{
public:
	GPTDiskPart();
	~GPTDiskPart();
	static GPTDiskPart *GPTDiskPartInstance();	
	int GPTDP_CreateGPTDiskPart(char *const ps8Path, unsigned char u8PartCount);
private:
    
	int GPTDP_Access(char *const ps8Path);
	int GPTDP_Open(char *const ps8Path,int s32Flag);
	int GPTDP_Ioctl(int s32Fd,int s32Cmd,void *pArg);
	int GPTDP_Close(int s32Fd);
	long long GPTDP_Lseek64(int s32Fd,long long s64Offset,int s32Whence);	
	int GPTDP_Select(int s32Fd,unsigned int u32TimeOut); 
	int GPTDP_Read(int s32Fd,unsigned char *pu8DateBuf,int s32Size);
	int GPTDP_Write(int s32Fd,unsigned char *pu8DateBuf,int s32Size);
    
    int GPTDP_WriteMBRHandle(int s32Fd,MBR_INFO_S *pstMBRInfo);
    int GPTDP_WriteGPTHead(int s32Fd,GPT_HEAD_INFO_S *pstGPTHeadInfo);
    int GPTDP_WritePartTable(int s32Fd,unsigned char u8PartCount,GPT_HEAD_INFO_S *pstGPTHeadInfo);

private:
	unsigned int        m_u32SecSize;         /*ÿ���������ֽ���*/
	unsigned int        m_u32HeadNum;         /*��ͷ��*/
	unsigned int        m_u32SecPerTrac;      /*ÿ���ŵ���������*/
	unsigned long long  m_u64SecCount;        /*�����ܵ�������*/

};

#endif

