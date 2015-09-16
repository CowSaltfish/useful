
// usefulDoc.h : CusefulDoc ��Ľӿ�
//


#pragma once
#include "usefulView.h"
#include "shpEngine/Feature.h"
#include "shpEngine/FeatureClass.h"
#include "shpEngine/DataSource.h"
class CusefulDoc : public CDocument
{
protected: // �������л�����
	CusefulDoc();
	DECLARE_DYNCREATE(CusefulDoc)

// ����
public:
	void load_triangle_file(tagTIN &tinNet,tagVEX &triVex,const char* pathFile);
	tagTIN m_tinNet;tagVEX m_triVex;BOOL m_triShow;
	
	void load_grid_file(tagGRID &grid,const char* pathFile);
	tagGRID m_grid;BOOL m_gridShow;

	FeatureClass* ImportShapeFileData( FILE* fpShp, FILE* fpDbf );
	void LoadAttributeData(Feature *pFeature, FILE* fpDbf, int everyRecordLen);
	int ReverseBytes(int n) ;
	FeatureClass* load_shapefile_file();
	DataSource& GetDataSource();

	std::vector<CString> m_dbfPath;
	std::vector<CString> m_shpPath;
	CString layerName;
	DataSource	 *m_pDataSource ;
	FeatureClass *m_pShpDataset ;
	BOOL		  m_shp_Show;

// ����
public:


// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CusefulDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnBPNet();
	afx_msg void OnLoadTriangle();
	afx_msg void OnLoadGrid();
	afx_msg void On3DView();
	afx_msg void OnClear();
	afx_msg void OnShpClear();
};
