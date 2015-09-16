
// usefulView.h : CusefulView ��Ľӿ�
//

#pragma once

#include "shpEngine/MapControl.h"
#include "shpEngine/DataSet.h"

#include <vector>
using namespace std;

struct TRIANGLE
{
	int paivertix[3];
	int piffacest[3];
};
struct TriVERTIX
{
	double padivertixX;
	double padivertixY;
};
struct GridVERTIX 
{
	double grid_x;
	double grid_y;
	double grid_value;
};
typedef vector<TRIANGLE>	tagTIN;
typedef vector<TriVERTIX>	tagVEX;
typedef vector<GridVERTIX>	tagGRID;

class CusefulDoc;
class CusefulView : public CView
{
protected: // �������л�����
	CusefulView();
	DECLARE_DYNCREATE(CusefulView)

// ����
public:
	CusefulDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//���ļ��е��������Σ����������δ���
	void draw_triangle(tagTIN tinNet,tagVEX triVex,CDC* pDC);
	void draw_grid(tagGRID grid,CDC *pDC);

	MapControl *m_pMapControl;
	BOOL        m_is_show_SHP;
	MapControl& CusefulView::GetMapControl();

// ʵ��
public:
	virtual ~CusefulView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShpFileOpen();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // usefulView.cpp �еĵ��԰汾
inline CusefulDoc* CusefulView::GetDocument() const
   { return reinterpret_cast<CusefulDoc*>(m_pDocument); }
#endif

