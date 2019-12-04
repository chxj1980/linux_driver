/************************************************************
*Copyright (C),lcb0281at163.com lcb0281atgmail.com
*FileName: gpt_struct.h
*BlogAddr: caibiao-lee.blog.csdn.net
*Description: GPT�ֱ��ͷ���ͷ��Ϣ�ṹ��
*Date:     2019-10-12
*Author:   Caibiao Lee
*Version:  V1.0
*Others:
*History:
***********************************************************/
#ifndef __HST_PART_STRUCT_H__
#define __HST_PART_STRUCT_H__

#define  GPT_HEAD_RESERVED   420

#pragma pack(1)

/**MBR ��������**/
typedef struct Part_info
{
	unsigned char   u8PartSelfFlag;        /**����ָʾ�� **/
	unsigned char   u8PartStartHead;       /**��ʼ��ͷ**/
	unsigned char   u8PartStartSec:6;      /**��ʼ����**/
	unsigned char   u8PartStartCylLow:2;   /**��ʼ����**/
	unsigned char   u8PartStartCylHig8;
	unsigned char   u8PartFlag;            /**ϵͳID**/
	unsigned char   u8PartStopHead;        /**������ͷ**/
	unsigned char   u8PartStopSec:6;       /**��������**/  
	unsigned char   u8PartStopCylLow:2;    /**��������**/
	unsigned char   u8PartStopCylHig8;
	unsigned int    u32StartSec;            /**���������*/
	unsigned int    u32SizeSec;             /**��������**/
}PART_INFO_S;

/**����������**/
typedef struct MBR_info
{
	unsigned char u8arrBoot[446];   /**Ӳ����������¼**/
	PART_INFO_S   starrPartInfo[4]; /**MBR ������**/ 
	unsigned char s8ArrTag[2];      /**������־(��Ч��־) 55 AA**/
}MBR_INFO_S;

/**GPT ������ͷ**/
typedef struct GPT_Head_Info
{
	unsigned char      u8arrSignature[8];       /**ǩ�� �̶�Ϊ:EFI PART**/
	unsigned char      u8arrVersion[4];         /**�汾��**/
	unsigned int       u32HeadLen;              /**GPTͷ���ܳ���**/
	unsigned int       u32GPTHeadCRC32;         /**GPTͷCRC32У���**/
	unsigned int       u32Reserved;             /**������������00**/
	unsigned long long u64GPTHeadPositSec;;     /**GPTͷ���ڵ�������**/
	unsigned long long u64GPTHeadBackupPositSec;/**GPTͷ�������ڵ�����**/
	unsigned long long u64GPTDataStartSec;      /**GPT��������ʼ����**/
	unsigned long long u64GPTDataEndSec;        /**GPT���������������**/  
	unsigned char      u8arrDiskGUID[16];       /**Ӳ��GUID**/ 
	unsigned long long u64GPTStartSec;          /**GPT������ʼ�����ţ�һ����2**/
	unsigned int       u32MaxNumPartTable;      /**������ɷ����������,һ��Ϊ128**/
	unsigned int       u32TableItemLen;         /**ÿ�����������ֽ�����һ��Ϊ128**/
	unsigned int       u32GPTCRC32;             /**������CRCУ���**/
	unsigned char      u8arrReserved[GPT_HEAD_RESERVED]; /**������һ���� 00**/
}GPT_HEAD_INFO_S;

/**GPT ������**/
typedef struct GPT_Info
{
	unsigned char    u8arrPartType[16];   /**��������**/
	unsigned char    u8arrGUID[16];       /**����GUID**/
	unsigned long long   u64PartStartSec; /**������ʼ����**/
	unsigned long long   u64PartStopSec;  /**������������**/
	unsigned long long   u64PartAttrFlag; /**������ǩ**/
	char    s8arrPartName[72];            /**��������**/
}GPT_INFO_S;

#pragma pack()

#endif

