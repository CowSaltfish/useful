#include "../stdafx.h"
#include <string.h>


#ifndef _READDBF_
#define _READDBF_

#define MAX_CHAR_LENGTH 256			//�ַ����ֶε���󳤶�

class CDBF
{
public:
	FILE *m_fpInFile;				//�����ļ�
	unsigned int m_uiRecLength;		//�ļ���¼�ĳ���
	unsigned int m_uiHeadFileLength;//�ļ��ṹ�������ֳ���
	unsigned long m_ulRecCount;		//�ļ���¼�ܸ���
	unsigned int m_uiFieldCount;	//�ֶεĸ��� 296 ��ʾ 263��������Ϣ��+ 1��ͷ��¼��ֹ����+ 32����һ���ֶ��Ӽ�¼����32 ���ֶ��Ӽ�¼�ĳ���
	char ***m_pCDBFInfo;			//�ļ���Ϣͷ
	unsigned long m_ulValidRecCount;//�ļ���Ч��¼�ܸ�����������������ɾ����ǵļ�¼
	unsigned long m_ulCurRecLine;	//��ǰ��¼�У��кŴ��㿪ʼ����
	char ***m_pszCondition;			//��������
	unsigned int m_uiCond;			//��������
	char *m_delLabel;				//ɾ����־

public:
	CDBF();
	virtual ~CDBF();

	bool ReadField(char *pcFieldName,char *pcResult,unsigned long ulSize); 	//����DBF��ָ���С�ָ���е�char������
	bool InitFieldInfo(char *pcFilePath);									//����DBF�е��ֶ���Ϣ
	bool SetGoLineNo(unsigned long ulGoLineNo);								//��������Ҫ�����������
	bool LogicDeleteCur();													//�߼�ɾ����ǰ��
	bool PhysicalPackCur();													//����ɾ����ǰ��
	bool PhysicalPack();													//����ɾ�����б�����ɾ����ǵ���
	bool ReplaceField(char *pcFieldName,char *pszContent,unsigned long ulSize);//д��dbf��ָ���С�ָ���е�char������
	bool AppendBlank();														//׷��һ����
	bool AppendDbf(char *pszFileName);										//������һ��dbf�ļ�׷�ӵ���dbf�ļ���,������ṹ����һ��												
	
	//bLoca��ʾ�ҵ����ݺ��Ƿ񽫵�ǰm_ulCurRecLine����ָ�����m_pszConditionʹ�������������磺
	//�������ֶ�Ҫ���ң�����=aa && ����>11 && ����<bb
	//m_pszCondition[0][0]=������m_pszCondition[0][1]=���䣬m_pszCondition[0][2]=����
	//m_pszCondition[1][0]=aa��m_pszCondition[1][1]=11��m_pszCondition[1][2]=bb
	//m_pszCondition[2][0]==��m_pszCondition[2][1]=>��m_pszCondition[2][2]=<����ʱ����ֻʵ����ȫ���
	bool Locate(bool bLoca);
	unsigned long Count();													//������������ļ�¼����
	bool CreateConditon(unsigned int uiCond);								//��������
	bool DestroyCondition();												//�ݻ�����
	bool SetCondition(char *pszFieldName,char *pszContent,char *pszCondPattern,unsigned int uiSerial);//��������
	bool AllTrim(char *pszContent);
};

#endif