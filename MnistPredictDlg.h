#pragma once

#include "bpnet/backprop.h"
// CMnistPredictDlg �Ի���
//bp net work to distinguish the mnist number
struct MNISTIMG 
{
	int mnist_row;
	int mnist_col;
	unsigned char* mnist_data;
};

class BPNetMnist:public BPNet
{
public:
	BPNetMnist(int imput_n,int hidden_n,int output_n)
	{
		bpnn_initialize(9);
		bp=bpnn_create(imput_n,hidden_n,output_n);
	}
	BPNetMnist(){bp=NULL;}

	//mnist ���ѵ����Ԥ��
	void BP_Mnist_Swap(char* buf);
	void BP_Mnist_Train(const char* pathMnist,const char* pathLabel,const char* pathBPNet,CProgressCtrl* progress);
	void BP_Mnist_Predict(const char* pathBPNet,const char* pathMnist,int num,CDC* pDC,CEdit* m_edit);

private:

	MNISTIMG BPNetMnist_Allocate(int rows,int cols);     //����ռ�
	void BPNetMnist_Free(MNISTIMG img);					 //ɾ���ռ�
};

class CMnistPredictDlg : public CDialog
{
	DECLARE_DYNAMIC(CMnistPredictDlg)

public:
	CMnistPredictDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMnistPredictDlg();

// �Ի�������
	enum { IDD = IDD_MNISTPREDICTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Train;
	CEdit m_Label;
	CEdit m_Test;
	CEdit m_Predict;
	CProgressCtrl m_progress;

	BPNetMnist m_BPNetMnist_MFC_Dlg;
	afx_msg void OnBPNetTrain();
	afx_msg void OnBPNetPredict();
};
