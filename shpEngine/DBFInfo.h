#pragma once
#include "ReadDBF.h"
#include <vector>



//����Field���ݿռ�
class DBFField
{
public:
	char  m_FieldData[128];		//����
	long  m_FieldIndex;			//��¼��ʾ
	char  m_IsDel;				//ɾ����־
public:
	DBFField()
	{
		memset(m_FieldData,0,sizeof(char)*128);
		m_IsDel=0;
	}
	void operator =(DBFField &filed);
};

typedef std::vector< DBFField >    DBFRecord;

//��������
class DBFFields
{
public:
	char			 m_FieldType;	  //��������
	char             m_FieldName[11]; //�ֶ�����
	long			 m_RecordCounts;  //��¼����
	DBFRecord        m_Records;	      //ÿ����¼	

public:
	DBFFields()
	{
		memset(m_FieldName,0,sizeof(char)*11);
	}
	void operator =(DBFFields &fields);
};

typedef std::vector < DBFFields >   DBFTable;

//��ȡһ������
long DBFColFieldData(CDBF &dbfFile,DBFFields &dbfField,int pos);

//��ȡһ������
long DBFFieldData(CDBF &dbfFile,DBFTable &dbfTable);

